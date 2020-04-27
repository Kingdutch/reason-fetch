type headers;
type responseCode = int;
type readableStream;

type responseError = [
  | `ResponseBodyRead(string)
  | `JsonParseError(string)
  | `UnknownError(string)
];

// TODO: The bodyUsed flag should be encoded in the type to avoid calling clone/json etc. twice.
type t = pri {
  ok:             bool,
  headers:        headers,
  redirected:     bool,
  status:         responseCode,
  statusText:     string,
  type_:          string, /* TODO: ENUM */
  body:           readableStream,
  bodyUsed:       bool,
};

let cloneRaw : t => (bool, t, string) = [%raw {|
  function (r) {
    try {
      return /* Ok */ [true, r.clone(), undefined];
    }
    catch (e) {
      return /* Error */ [false, undefined, e.message];
    }
  }
|}];
let clone : t => result(t, responseError) = r => switch(cloneRaw(r)) {
  | (true, c, _) => Ok(c)
  | (false, _, e) => Error(`ResponseBodyRead(e))
};

[@bs.send]
external error : t => t = "error";

[@bs.send]
external redirect : (t, string, int) => t = "redirect";

[@bs.send]
external jsonRaw : t => Promise.Js.t(Js.Json.t, Js.Exn.t) = "json";
let getJsonErrorType : Js.Exn.t => string = [%raw {|
  function (e) {
    if (e instanceof TypeError) {
      return "ResposeBodyRead";
    }
    else if (e instanceof SyntaxError) {
      return "JsonParseError";
    }
    else {
      return "";
    }
  }
|}];

// Helper method to covert Optio(string) to (empty) string.
let unpackExceptionMessage = e => switch (Js.Exn.message(e)) {
  | Some(s) => s
  | None => ""
}

let json = (t) => {
  t
   ->jsonRaw
   ->Promise.Js.toResult
   ->Promise.mapError(e => switch(getJsonErrorType(e)) {
    | "ResponseBodyRead" => `ResponseBodyRead(unpackExceptionMessage(e))
    | "JsonParseError" => `JsonParseError(unpackExceptionMessage(e))
    | _ => `UnknownError(unpackExceptionMessage(e))
   })
};

[@bs.send]
external text : t => string = "text";

// TODO: Implement arrayBuffer, blob and formData.
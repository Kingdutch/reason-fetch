type fetchError = [
  | `FetchError(string)
  | `FetchAborted
];

type init = Kingdutch__ReasonFetch__Init.t;

// Simple binding to the browser fetch function returning a rejectable promise.
[@bs.val]
external fetchRaw : (string, ~init: init = ?, unit) => Promise.Js.t(Kingdutch__ReasonFetch__Response.t, Js.Exn.t) = "fetch";

// Raw JS code to determine the error type.
let getErrorType : Js.Exn.t => string = [%raw {|
  function (e) {
    if (e instanceof DOMException) {
      return "aborted";
    }
    else if (e instanceof TypeError) {
      return "type";
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

// User-facing function to convert a rejectable promise into a TypeSafe promise
// that resolves to a result object.
let fetch  = (~init=?, url)  => {
  fetchRaw(url, ~init?, ())
  -> Promise.Js.toResult
  -> Promise.mapError(e => switch(getErrorType(e)) {
    | "aborted" => `FetchAborted
    | "type" => `FetchError(unpackExceptionMessage(e))
    | _ => `FetchError("Fetch was rejected with an error of an unknown type which could indicate an error in the Fetch spec implementation")
  })
}

// TODO: Implement fromRequest (second option for input type).
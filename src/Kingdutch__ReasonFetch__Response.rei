type headers;
type responseCode = int;
type readableStream;

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

let clone : t => result(t, [> `ResponseBodyRead(string)]);

[@bs.send]
external error : t => t = "error";

[@bs.send]
external redirect : (t, string, int) => t = "redirect";

let json : t => Promise.t(result(Js.Json.t, [> `ResponseBodyRead(string) | `JsonParseError(string) | `UnknownError(string)]));

[@bs.send]
external text : t => string = "text";

// TODO: Implement arrayBuffer, blob and formData.
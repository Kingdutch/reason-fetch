type init = Kingdutch__ReasonFetch__Init.t;

let fetch : (~init: init=?, string) => Promise.t(result(Kingdutch__ReasonFetch__Response.t, [> `FetchError(string) | `FetchAborted]));

let fetchErrorToString : [< | `ResponseBodyRead(string)
                            | `JsonParseError(string)
                            | `UnknownError(string)
                            | `FetchError(string)
                            | `FetchAborted ] => string;
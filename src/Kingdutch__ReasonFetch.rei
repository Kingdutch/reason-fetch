module AbortController = Kingdutch__ReasonFetch__AbortController;
module Init = Kingdutch__ReasonFetch__Init;
module Response = Kingdutch__ReasonFetch__Response;
module Headers = Kingdutch__ReasonFetch__Headers;

type init = Kingdutch__ReasonFetch__Init.t;

let fetch:
  (~init: init=?, string) =>
  Promise.t(
    result(
      Kingdutch__ReasonFetch__Response.t,
      [> | `FetchError(string) | `FetchAborted],
    ),
  );

let fetchErrorToString:
  [<
    | `ResponseBodyRead(string)
    | `JsonParseError(string)
    | `UnknownError(string)
    | `FetchError(string)
    | `FetchAborted
  ] =>
  string;
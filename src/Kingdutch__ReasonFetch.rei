type fetchError = [
  | `FetchError(string)
  | `FetchAborted
];

type init = Kingdutch__ReasonFetch__Init.t;

let fetch : (~init: init=?, string) => Promise.t(result(Kingdutch__ReasonFetch__Response.t, fetchError));
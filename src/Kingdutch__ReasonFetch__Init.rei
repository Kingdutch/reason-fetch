type headers;
type bodyInit;

[@bs.deriving abstract]
type t = {
  [@bs.optional] _method:        string,
  [@bs.optional] headers:        headers,
  [@bs.optional] body:           bodyInit,
  [@bs.optional] referrer:       string,
  [@bs.optional] referrerPolicy: string,
  [@bs.optional] mode:           string,
  [@bs.optional] credentials:    string,
  [@bs.optional] cache:          string,
  [@bs.optional] redirect:       string,
  [@bs.optional] integrity:      string,
  [@bs.optional] keepalive:      bool,
  [@bs.optional] signal:         Kingdutch__ReasonFetch__AbortController.signal,
};

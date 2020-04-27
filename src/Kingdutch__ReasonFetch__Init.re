type t;

type headers;
type bodyInit;
type signal;

[@bs.obj]
external make : (
  ~_method:        string=?,
  ~headers:        headers=?,
  ~body:           bodyInit=?,
  ~referrer:       string=?,
  ~referrerPolicy: string=?,
  ~mode:           string=?,
  ~credentials:    string=?,
  ~cache:          string=?,
  ~redirect:       string=?,
  ~integrity:      string=?,
  ~keepalive:      bool=?,
  ~signal:         signal=?,
  unit
) => t = "";

let make = (
  ~_method = ?,
  ~headers = ?,
  ~body = ?,
  ~referrer = ?,
  ~referrerPolicy = ?,
  ~mode = ?,
  ~credentials = ?,
  ~cache = ?,
  ~redirect = ?,
  ~integrity = ?,
  ~keepalive = ?,
  ~signal = ?,
  ()
) => make(
  ~_method?,
  ~headers?,
  ~body?,
  ~referrer?,
  ~referrerPolicy?,
  ~mode?,
  ~credentials?,
  ~cache?,
  ~redirect?,
  ~integrity?,
  ~keepalive?,
  ~signal?,
  ()
);
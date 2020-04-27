// Tell users they should open the console for the output.
[@bs.scope "document"] [@bs.val]
external documentWrite : string => unit = "write"
documentWrite("Open the console for output.");

// A simple result printer to convert an `option` to a console message.
let result_printer = message => result => switch (result) {
  | Ok(s) => { Js.log2(message, "ok"); Js.log(s); }
  | Error(`FetchError(s)) => { Js.log2(message, "fetch error"); Js.log(s); }
  | Error(`FetchAborted) => { Js.log2(message, "fetch aborted"); }
};

open Kingdutch__ReasonFetch;
module Init = Kingdutch__ReasonFetch__Init;

// Successful request
fetch("https://httpbin.org/get")
->Promise.get(result_printer("/get"));

// Fetch 404 error code
fetch("https://httpbin.org/status/404")
->Promise.get(result_printer("/status/404"));

// Fetch nonexistent service
fetch("http://localhost:9001")
->Promise.get(result_printer("localhost:9001"));

// Fetch POST with some data
fetch("https://httpbin.org/post", ~init=Init.make(~_method="POST", ()))
->Promise.get(result_printer("/post"));

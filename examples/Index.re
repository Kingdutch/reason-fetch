// Tell users they should open the console for the output.
[@bs.scope "document"] [@bs.val]
external documentWrite: string => unit = "write";
documentWrite("Open the console for output.");

// A simple result printer to convert an `option` to a console message.
let result_printer = (message, result) =>
  switch (result) {
  | Ok(s) =>
    Js.log2(message, "ok");
    Js.log(s);
  | Error(`FetchError(s)) =>
    Js.log2(message, "fetch error");
    Js.log(s);
  | Error(`FetchAborted) => Js.log2(message, "fetch aborted")
  };

open Kingdutch__ReasonFetch;
module AbortController = Kingdutch__ReasonFetch__AbortController;
module Init = Kingdutch__ReasonFetch__Init;

// Successful request
fetch("https://httpbin.org/get")->Promise.get(result_printer("/get"));

// Fetch 404 error code
fetch("https://httpbin.org/status/404")
->Promise.get(result_printer("/status/404"));

// Fetch nonexistent service
fetch("http://localhost:9001")
->Promise.get(result_printer("localhost:9001"));

// Fetch POST with some data
fetch("https://httpbin.org/post", ~init=Init.t(~_method="POST", ()))
->Promise.get(result_printer("/post"));

// Trigger a CORS error.
fetch("https://httpbin.org/get", ~init=Init.t(~mode="same-origin", ()))
->Promise.get(result_printer("CORS Error /get"));

// Example of an aborted fetch.
let controller = AbortController.make();
fetch(
  "http://httpbin.org/bytes/1024",
  ~init=Init.t(~signal=controller.signal, ()),
)
->Promise.get(result_printer("/bytes/1024"));
controller->AbortController.abort;

// Example of fetching JSON data.
fetch("http://httpbin.org/json")
->Promise.flatMapOk(Kingdutch__ReasonFetch__Response.json)
->Promise.mapOk(json => {
    Js.log("/json");
    Js.log(json);
  })
->Promise.mapError(fetchErrorToString)
->Promise.getError(Js.log);

Js.log(Kingdutch__ReasonFetch__Headers.make());
let h =
  Kingdutch__ReasonFetch__Headers.makeFromObject({
    "Content-Type": "text/html",
  });
h->Kingdutch__ReasonFetch__Headers.append("e-tag", "555");
h->Kingdutch__ReasonFetch__Headers.entries->Js.log;
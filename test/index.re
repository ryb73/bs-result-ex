open Belt.Result;
open ResEx;

let get = fun
    | Some(x) => x
    | None => failwith("error");

Ok("yeah")
|> map(_, (++)(" ok"))
|> toOpt
|> get
|> Js.log;

Error("oh")
|> mapError((++)(" an error"))
|> getError
|> Js.log;

[| Ok(1), Ok(2), Ok(3) |]
|> elevateArray
|> Js.log;

[| ok(1), error("nah"), ok(3) |]
|> elevateArray
|> Js.log;

try (Error("Nothing!") |> ResEx.getExn) {
    | e => Js.Exn.asJsExn(e) |> Js.log
};

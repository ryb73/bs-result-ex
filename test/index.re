open Belt.Result;
open ResultEx;

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

[| Ok(1), Error("nah"), Ok(3) |]
|> elevateArray
|> Js.log;

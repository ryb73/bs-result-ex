open Belt.Result;

exception NoValue;

let toOpt = fun
    | Ok(v) => Some(v)
    | _ => None;

let fromOpt = (error) => fun
    | None => Error(error)
    | Some(v) => Ok(v);

let getError = fun
    | Error(e) => Some(e)
    | _ => None;

let bindError = (callback) => fun
    | Ok(v) => Ok(v)
    | Error(e) => callback(e);

let mapError = (callback) => bindError(e => Error(callback(e)));

let getExn = fun
    | Ok(v) => v
    | Error(_) => raise(NoValue);

let elevateArray = (array) =>
    array
    |> Js.Array.reduce((acc, result) =>
        switch (acc, result) {
            | (Error(_), _) => acc
            | (_, Error(_) as error) => error
            | (Ok(arr), Ok(result)) => Ok(Js.Array.concat([| result |], arr))
        }
    , Ok([||]));
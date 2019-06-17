open Belt.Result;

let ok = v => Ok(v);
let error = v => Error(v);

let toOpt = fun
    | Ok(v) => Some(v)
    | Error(_) => None;

let fromOpt = (error) => fun
    | None => Error(error)
    | Some(v) => Ok(v);

let getError = fun
    | Error(e) => Some(e)
    | Ok(_) => None;

let bindError = (callback) => fun
    | Ok(v) => Ok(v)
    | Error(e) => callback(e);

let mapError = (callback) => bindError(e => Error(callback(e)));

let raiseExn = (payload) => {
    Js.Promise.resolve(payload) |> ignore;
    let err = [%bs.raw {| new Error("ResEx.getExn") |}];
    Js.Dict.set(err, "payload", payload);
    raise(err);
};

let getExn = fun
    | Ok(v) => v
    | Error(payload) => raiseExn(payload);

let elevateArray = (array) =>
    array
    |> Js.Array.reduce((acc, result) =>
        switch (acc, result) {
            | (Error(_), _) => acc
            | (_, Error(_) as error) => error
            | (Ok(arr), Ok(result)) => Ok(Js.Array.concat([| result |], arr))
        }
    , Ok([||]));
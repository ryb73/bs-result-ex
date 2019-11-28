open Jest;
open Expect;
open ResEx;

test("ok", () =>
    expect(ok(123))
    |> toEqual(Belt.Result.Ok(123))
);

test("error", () =>
    expect(error(123))
    |> toEqual(Belt.Result.Error(123))
);

describe("get", () => {
    test("ok", () =>
        ok(123)
        |> get
        |> expect
        |> toEqual(Some(123))
    );

    test("error", () =>
        error(123)
        |> get
        |> expect
        |> toEqual(None)
    );
});

describe("getError", () => {
    test("ok", () =>
        ok(123)
        |> getError
        |> expect
        |> toEqual(None)
    );

    test("error", () =>
        error(123)
        |> getError
        |> expect
        |> toEqual(Some(123))
    );
});

describe("getExn", () => {
    test("ok", () =>
        ok(123)
        |> ResEx.getExn
        |> expect
        |> toBe(123)
    );

    test("error", () =>
        (() => error("err") |> ResEx.getExn)
        |> expect
        |> toThrow
    );
});

describe("fromOpt", () => {
    test("ok", () =>
        Some(123)
        |> fromOpt("error")
        |> expect
        |> toEqual(ok(123))
    );

    test("error", () =>
        None
        |> fromOpt("error")
        |> expect
        |> toEqual(error("error"))
    );
});

describe("bindError", () => {
    test("ok", () =>
        ok(123)
        |> bindError(() => ok(999))
        |> expect
        |> toEqual(ok(123))
    );

    test("error", () =>
        error("nothin")
        |> bindError(e => ok(e ++ ", ok?"))
        |> expect
        |> toEqual(ok("nothin, ok?"))
    );
});

describe("mapError", () => {
    test("ok", () =>
        ok(123)
        |> mapError(() => ok(999))
        |> expect
        |> toEqual(ok(123))
    );

    test("error", () =>
        error("nothin")
        |> mapError(e => e ++ ", ok?")
        |> expect
        |> toEqual(error("nothin, ok?"))
    );
});

describe("elevateArray", () => {
    test("ok", () =>
        [| ok(1), ok(2), ok(3) |]
        |> elevateArray
        |> expect
        |> toEqual(ok([| 1, 2, 3 |]))
    );

    test("error", () =>
        [| ok(1), error("nah"), ok(3) |]
        |> elevateArray
        |> expect
        |> toEqual(error("nah"))
    );
});

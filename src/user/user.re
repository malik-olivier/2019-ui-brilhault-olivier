let encodeUser = (email,password,firstname,lastname) =>
    Json.Encode.(object_([("email", string(email)), ("password", string(password)),("firstName", string(firstname)),("lastName", string(lastname))]));

module Decode = {
    let response = json =>
        Json.Decode.{
            "success": json |> field("success", bool),
            "message": json |> field("message", string)
        }
    };
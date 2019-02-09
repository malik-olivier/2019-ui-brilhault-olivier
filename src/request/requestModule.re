type method =
    | POST
    | PUT
    | DELETE
    | GET;


let postExecute = (url : string,body) => 
        Js.Promise.(
            Fetch.fetchWithInit(
            url,
            Fetch.RequestInit.make(
                    ~method_=Post,
                    ~body=Fetch.BodyInit.make(Js.Json.stringify(body)),
                    ~headers=Fetch.HeadersInit.make({"mode" : "cors","Content-Type": "application/json","Access-Control-Allow-Origin": "*"}),
                    ()
                    )
            )
            |> then_(value => {
                Js.log(value);
                Js.Promise.resolve(value);
              })
            |> then_(value2 => {Js.log("heu"); Js.Promise.resolve()})
            /* |> catch_(err => {
                /* Js.log(err); */
                Js.Promise.resolve(); });  */
        )

    
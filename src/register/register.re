open RequestModule;
open User;

type action =
  | UpdateEmail(string)
  | UpdateFirstName(string)
  | UpdateLastName(string)
  | UpdatePassword(string)
  | Register
  | RedirectToLogin;

type state = {
  email: string,
  password: string,
  firstname: string,
  lastname: string,
  error: string,
};

let component = ReasonReact.reducerComponent("Register");

let make = _children => {
  ...component,
  initialState: () => {email: "", firstname: "", lastname: "", password: "", error: ""},
  reducer: (action, state) =>
    switch (action) {
    | UpdateEmail(p) => ReasonReact.Update({...state, email: p})
    | UpdateFirstName(p) => ReasonReact.Update({...state, firstname: p})
    | UpdateLastName(p) => ReasonReact.Update({...state, lastname: p})
    | UpdatePassword(p) => ReasonReact.Update({...state, password: p})
    | Register =>
      ReasonReact.SideEffects(
        _self =>
          /* let u = user(state.email,state.password,state.firstname,state.lastname) |> */
          if (state.email != "" && state.password != "" && state.firstname != "" && state.lastname != "") {
            Js.log(Js.Json.stringify(encodeUser(state.email, state.password, state.firstname, state.lastname)));
            let promise =
              postExecute(
                "http://localhost:8080/api/v1/users",
                encodeUser(state.email, state.password, state.firstname, state.lastname),
              );
            ();
            /* |> Js.Promise.catch(err => {
                 Js.log("Failure!!", err);
                 ReasonReact.Update({...state,error : err})
                 Js.Promise.resolve(-2);
               }); */
          } else {
            Js.log(state.error);
            ReasonReact.Update({...state, error: "Field(s) missing"});
            Js.log("error field(s) missing");
          },
      )
    | RedirectToLogin => ReasonReact.Update({...state, firstname: state.password})
    //      ReasonReact.Router.push(http://localhost:1234/login);
    },
  render: self =>
    <div>
      <h1> {ReasonReact.string("Register for the best application")} </h1>
      <h2> {self.state.firstname |> ReasonReact.string} </h2>
      <div>
        <div>
          <span>
            {ReasonReact.string("FirstName : ")}
            <input
              type_="text"
              onChange={_evt => self.send(UpdateFirstName(ReactEvent.Form.target(_evt)##value))}
            />
          </span>
        </div>
        <div>
          <span>
            {ReasonReact.string("LastName : ")}
            <input type_="text" onChange={_evt => self.send(UpdateLastName(ReactEvent.Form.target(_evt)##value))} />
          </span>
        </div>
        <div>
          <span>
            {ReasonReact.string("Email : ")}
            <input type_="email" onChange={_evt => self.send(UpdateEmail(ReactEvent.Form.target(_evt)##value))} />
          </span>
        </div>
        <div>
          <span>
            {ReasonReact.string("Password : ")}
            <input
              type_="password"
              onChange={_evt => self.send(UpdatePassword(ReactEvent.Form.target(_evt)##value))}
            />
          </span>
        </div>
        <div>
          <button onClick={_ => self.send(Register)}> {ReasonReact.string("Register")} </button>
          <button onClick={_ => ReasonReact.Router.push("/login")}> {ReasonReact.string("Log in")} </button>
        </div>
        <div id="error"> {self.state.error |> ReasonReact.string} </div>
      </div>
    </div>,
};

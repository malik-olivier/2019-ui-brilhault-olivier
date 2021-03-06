open RequestModule;
open User;

[@bs.val] external apiUri: string = "process.env.API_URL";

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
            postExecute(apiUri, encodeUser(state.email, state.password, state.firstname, state.lastname), () =>
              ReasonReact.Router.push("score")
            );
          } else {
            ReasonReact.Update({...state, error: "Field(s) missing"});
            Js.log("error field(s) missing");
            alert("error field(s) missing")
          },
      )
    | RedirectToLogin =>
      ReasonReact.Router.push("login");
      ReasonReact.NoUpdate;
    },
  render: self =>
    <div>
      <h1> {ReasonReact.string("Register for the best application")} </h1>
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
          <button onClick={_ => self.send(RedirectToLogin)}> {ReasonReact.string("Log in")} </button>
        </div>
        <div id="error"> {self.state.error |> ReasonReact.string} </div>
      </div>
    </div>,
};

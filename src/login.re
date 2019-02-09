type action =
  | UpdateEmail(string)
  | UpdatePassword(string)
  | RedirectToScore
  | Login
  | RedirectToRegister;

type state = {
  email: string,
  password: string,
};

let component = ReasonReact.reducerComponent("Login");

let make = _children => {
  ...component,
  initialState: () => {email: "", password: ""},
  reducer: (action, state) =>
    switch (action) {
    | UpdateEmail(p) => ReasonReact.Update({...state, email: p})
    | UpdatePassword(p) => ReasonReact.Update({...state, password: p})
    | RedirectToScore => ReasonReact.Update({...state, email: state.email})
    | Login => ReasonReact.Update({...state, password: state.password})
    | RedirectToRegister => ReasonReact.Update({...state, email: state.email})
    },
  render: self =>
    <div>
      <h1> {ReasonReact.string("Log in into the best application")} </h1>
      <div>
        <div>
          <span>
            {ReasonReact.string("Email : ")}
            <input type_="text" onChange={_evt => self.send(UpdateEmail(ReactEvent.Form.target(_evt)##value))} />
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
          <button onClick={_ => self.send(RedirectToRegister)}> {ReasonReact.string("Register")} </button>
          <button onClick={_ => self.send(Login)}> {ReasonReact.string("Log in")} </button>
        </div>
      </div>
    </div>,
};
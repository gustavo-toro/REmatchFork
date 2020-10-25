import React from "react";
import {
  BrowserRouter as Router,
  Switch,
  Route,
  Link
} from "react-router-dom";

import { createMuiTheme, ThemeProvider } from '@material-ui/core/styles';
import CssBaseline from "@material-ui/core/CssBaseline";

import AboutInterface from './components/AboutInterface';
import MainInterface from './components/Maininterface';

/* MATERIAL UI DARK THEME */
const darkTheme = createMuiTheme({
  palette: {
    type: 'dark',
    primary: {
      main: '#03DAC6',
    },
    secondary: {
      main: '#FCE938',
    },
    background: {
      paper: '#212121',
      default: '#353535',
    }
  },
});

const App = () => {
  return (
    <ThemeProvider theme={darkTheme}>
      <CssBaseline />
      <Router>
        <nav style={{ backgroundColor: 'rgb(3, 218, 198)' }}>
          <Link to="/">
            Home
            </Link>
          <br />
          <Link to="/about">
            About
            </Link>
        </nav>
        <Switch>
          <Route path="/about">
            <AboutInterface />
          </Route>
          <Route path="/">
            <MainInterface />
          </Route>
        </Switch>
      </Router>
    </ThemeProvider>
  )
}

export default App;
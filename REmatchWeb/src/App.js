/*

TODO:
* ABOUT ****

* SEND A FINISHED MESSAGE FROM WORKER FOR ENABLING/DISABLING INPUT
  ALSO DISPLAY PROCESSING OR SOMETHING TIEMPO
* MESSAGE OF ERROR IF OOM
* HANDLE EDIT QUERY/TEXT ** Matches (old)
* SIDE DRAWER X
*/

import React from "react";
import {
  BrowserRouter as Router,
  Switch,
  Route,
} from "react-router-dom";

import { createMuiTheme, ThemeProvider } from '@material-ui/core/styles';
import CssBaseline from "@material-ui/core/CssBaseline";

import Navbar from './components/Navbar';
import About from './components/About';
import Home from './components/Home';
import 'fontsource-roboto';

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
      default: '#424242',
    }
  },
});

const App = () => {
  return (
    <ThemeProvider theme={darkTheme}>
      <CssBaseline />
      <Router>
        <Navbar/>
        <Switch>
          <Route path="/about">
            <About />
          </Route>
          <Route path="/">
            <Home />
          </Route>
        </Switch>
      </Router>
    </ThemeProvider>
  )
}

export default App;
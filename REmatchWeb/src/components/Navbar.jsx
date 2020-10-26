import React from 'react';

import { Link } from 'react-router-dom';

import AppBar from '@material-ui/core/AppBar';
import Toolbar from '@material-ui/core/Toolbar';
import IconButton from '@material-ui/core/IconButton';

import Menu from '@material-ui/icons/Menu';

import Logo from '../assets/logo-dark.png';

const Navbar = () => (

  <AppBar position="fixed" className="appBar">
    <Toolbar>
      <IconButton
        color="primary"
        edge="start">
        <Menu />
      </IconButton>
      <Link to="/">
        <img className="logo" src={Logo} alt="REmatch" />
      </Link>
      <Link to="/about" style={{ color: 'yellow', right: 0, position: 'relative' }}>
        ABOUT (ESTO ES TEMPORAL)
        </Link>
    </Toolbar>
  </AppBar>
)

export default Navbar;
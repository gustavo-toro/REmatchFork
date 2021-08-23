import React from 'react';

import Container from '@material-ui/core/Container';
import Typography from '@material-ui/core/Typography';
import Paper from '@material-ui/core/Paper';

import Viewer from './Viewer';

import english from '../text/english';

const Advanced = () => {
  return (
    <Container maxWidth="sm" className="mainContainer">
        <Typography variant="h5" color="primary" align="center">Advanced tutorial</Typography>
        <Typography variant="subtitle1" color="primary">
          How is rematch different from common regex?
        </Typography>
    </Container>
  )
}

export default Advanced;
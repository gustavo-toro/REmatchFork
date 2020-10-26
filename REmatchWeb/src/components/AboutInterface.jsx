import React from 'react';

import Container from '@material-ui/core/Container';

import LiteViewer from './LiteViewer';

const AboutInterface = () => {
  return (
    <Container maxWidth="sm">
      <div style={{marginTop: 128, marginBottom: 128}}>
      <LiteViewer idx="example1" rematch="!x{.+}!y{.+}!z{.+}!w{.+}" text="aaaaaa"/>
      <br/>
      <LiteViewer idx="example2" rematch="!y{.+}" text="Text abb"/>
      </div>
    </Container>
  )
}

export default AboutInterface;
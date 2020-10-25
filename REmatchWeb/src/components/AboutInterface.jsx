import React from 'react';

import Container from '@material-ui/core/Container';

import LiteViewer from './LiteViewer';

const AboutInterface = () => {
  return (
    <Container maxWidth="sm">
      <div style={{marginTop: 128}}>
      <LiteViewer idx="example1" query="!x{.+} !y{jaja<1,32>} !z{\n} !w{\s}" text="Text aaa"/>
      <br/>
      <LiteViewer idx="example2" query="!y{.+}" text="Text abb"/>
      <br/>
      <LiteViewer idx="example3" query="!z{.+}" text="Text aaa"/>
      </div>
    </Container>
  )
}

export default AboutInterface;
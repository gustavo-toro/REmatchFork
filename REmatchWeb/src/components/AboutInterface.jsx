import React from 'react';

import Container from '@material-ui/core/Container';

import LiteViewer from './LiteViewer';
import LiteViewerVs from './LiteViewerVs';

const AboutInterface = () => {
  return (
    <Container maxWidth="sm">
      <div style={{ marginTop: 128, marginBottom: 128 }}>
        <LiteViewerVs idx="example4" rematch="!x{jaja REmatch es mejor}" regex="Noo yo tambien soy util :C" text="jaja REmatch es mejor, Noo yo tambien soy util :C"/>
        <br />
        <LiteViewer idx="example2" rematch="!y{.+}" text="Text abb" />
        <br />
        <LiteViewer idx="example3" rematch="!name{c.+}@!domain{.+com}" text="cristian.riveros@gmail.com" />
        <br />
        <LiteViewer idx="example1" rematch="!x{.+}!y{.+}!z{.+}!w{.+}" text="aaaaaa" />
      </div>
    </Container>
  )
}

export default AboutInterface;
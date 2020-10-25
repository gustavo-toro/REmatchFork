import React from 'react';

import Container from '@material-ui/core/Container';
import Paper from '@material-ui/core/Paper';
import Divider from '@material-ui/core/Divider';
import Grid from '@material-ui/core/Grid';
import Select from '@material-ui/core/Select';
import MenuItem from '@material-ui/core/MenuItem';
import Button from '@material-ui/core/Button';

import SectionTitle from './SectionTitle';

const AboutInterface = () => {
  return (
    <Container>
      <Select
        value={1}>
        <MenuItem value={1}>Example 1</MenuItem>
        <MenuItem value={2}>Example n</MenuItem>
      </Select>

      <Paper className="versusContainer" elevation={2}>
        <Grid container>
          <Grid item xs={12}>
            <SectionTitle title="REgex" />
          </Grid>
          {/* REGEX */}
          <Grid item xs={12} className="codeContainer">
            <div className="code">
              {'.*!x{a+}!y{b+}.*'}
            </div>
            <Divider orientation="vertical" flexItem />
            <div className="code">
              {'(a+)(b+)'}
            </div>
          </Grid>
          <Grid item xs={12}>
            <SectionTitle title="Text" />
            <Grid item xs={12} className="codeContainer">
              <div className="code" style={{height: 500}}>
                1 Example text :)<br/>
                2 Example text :)<br/>
                3 Example text :)<br/>
                4 Example text :)<br/>
                5 Example text :)<br/>
                6 Example text :)<br/>
                7 Example text :)<br/>
              </div>
            </Grid>
          </Grid>
          <Grid item xs={12}>
            <Button color="primary" variant="contained" style={{width: '100%'}}>
              Compare!
            </Button>
          </Grid>
        </Grid>
      </Paper>
    </Container>
  )
}

export default AboutInterface;
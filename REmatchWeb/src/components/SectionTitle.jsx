import React from 'react';

import Typography from '@material-ui/core/Typography';
import Box from '@material-ui/core/Box';

const SectionTitle = ({ title }) => (
  <Typography variant="body2" component="div" className="sectionTitle">
    <Box fontWeight="fontWeightBold">
      {title}
    </Box>
  </Typography>
)

export default SectionTitle;
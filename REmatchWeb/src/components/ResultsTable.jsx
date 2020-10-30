import React, { useState, useEffect } from 'react';

import Grid from '@material-ui/core/Grid';
import Table from '@material-ui/core/Table';
import TableBody from '@material-ui/core/TableBody';
import TableCell from '@material-ui/core/TableCell';
import TableContainer from '@material-ui/core/TableContainer';
import TableHead from '@material-ui/core/TableHead';
import TableRow from '@material-ui/core/TableRow';
import Select from '@material-ui/core/Select';
import MenuItem from '@material-ui/core/MenuItem';
import Pagination from '@material-ui/lab/Pagination';
import Tooltip from '@material-ui/core/Tooltip';
import Button from '@material-ui/core/Button';
import Backdrop from '@material-ui/core/Backdrop';

import GetApp from '@material-ui/icons/GetApp';

const ResultsTable = ({
  matches,
  schema,
  textEditor,
  addMarks,
  clearMarks
}) => {
  const [state, setState] = useState({
    page: 0,
    rowsPerPage: 25,
    open: false,
  });

  const handleChangePage = (_, newPage) => {
    setState(prevState => ({ ...prevState, page: newPage - 1 }));
  }

  const handleChangeRowsPerPage = (e) => {
    setState(prevState => ({ ...prevState, page: 0, rowsPerPage: e.target.value }));
  }

  const handleMarkText = (row) => {
    clearMarks();
    addMarks(row);
  }

  const download = (content, filename) => {
    let element = document.createElement('a');
    element.setAttribute('href', 'data:text/plain;charset=utf-8,' + encodeURIComponent(content));
    element.setAttribute('download', filename);
    element.style.display = 'none';
    document.body.appendChild(element);
    element.click();
    document.body.removeChild(element);
  }

  const exportCSV = () => {
    let curr, CSVString = schema.join(',') + '\n';
    matches.forEach((match) => {
      curr = []
      match.forEach((span) => {
        curr.push(textEditor.getRange(textEditor.posFromIndex(span[0]), textEditor.posFromIndex(span[1])));
      })
      CSVString += curr.join(',') + '\n';
    })

    download(CSVString, `REmatch-${Date.now()}.csv`);
  }

  useEffect(() => {
    if (matches.length === 0) {
      setState(prevState => ({ ...prevState, page: 0 }));
    }
  }, [matches]);

  const exportJSON = () => {
    let curr, JSONString = '[\n';
    matches.forEach((match) => {
      curr = []
      match.forEach((span, idx) => {
        curr.push(`\t\t'${schema[idx]}': '${textEditor.getRange(textEditor.posFromIndex(span[0]), textEditor.posFromIndex(span[1]))}'`);
      });
      JSONString += '\t{\n'
      JSONString += curr.join(',\n')
      JSONString += '\n\t},\n'
    })
    JSONString += ']'
    download(JSONString, `REmatch-${Date.now()}.json`);
  }

  useEffect(() => {
    if (matches.length === 0) {
      setState(prevState => ({ ...prevState, page: 0 }));
    }
  }, [matches]);

  return (
    <>
      <Backdrop 
        open={state.open} 
        onClick={() => setState(prevState => ({...prevState, open: false}))}
        style={{ zIndex: 6000, display: 'flex', gap: '1rem' }}>
        <Button
          color="primary"
          style={{fontWeight: 'bold'}}
          startIcon={
            <svg style={{width:24, height: 24}} viewBox="0 0 24 24">
              <path fill="currentColor" d="M14 2H6C4.9 2 4 2.9 4 4V20C4 21.1 4.9 22 6 22H18C19.1 22 20 21.1 20 20V8L14 2M18 20H6V4H13V9H18V20M10 19L12 15H9V10H15V15L13 19H10" />
            </svg>
          }
          // src=https://materialdesignicons.com/
          size="large"
          variant="contained"
          onClick={exportCSV}>
          Export as CSV
        </Button>
        <Button
          color="secondary"
          style={{fontWeight: 'bold'}}
          startIcon={
            // src=https://materialdesignicons.com/
            <svg style={{width:24, height: 24}} viewBox="0 0 24 24">
              <path fill="currentColor" d="M5,3H7V5H5V  10A2,2 0 0,1 3,12A2,2 0 0,1 5,14V19H7V21H5C3.93,20.73 3,20.1 3,19V15A2,2 0 0,0 1,13H0V11H1A2,2 0 0,0 3,9V5A2,2 0 0,1 5,3M19,3A2,2 0 0,1 21,5V9A2,2 0 0,0 23,11H24V13H23A2,2 0 0,0 21,15V19A2,2 0 0,1 19,21H17V19H19V14A2,2 0 0,1 21,12A2,2 0 0,1 19,10V5H17V3H19M12,15A1,1 0 0,1 13,16A1,1 0 0,1 12,17A1,1 0 0,1 11,16A1,1 0 0,1 12,15M8,15A1,1 0 0,1 9,16A1,1 0 0,1 8,17A1,1 0 0,1 7,16A1,1 0 0,1 8,15M16,15A1,1 0 0,1 17,16A1,1 0 0,1 16,17A1,1 0 0,1 15,16A1,1 0 0,1 16,15Z" />
            </svg>
          }
          size="large"
          variant="contained"
          onClick={exportJSON}>
          Export as JSON
        </Button>
      </Backdrop>


      <Grid container>
        <Grid item md={8} sm={6} xs={12} style={{ padding: '.5rem 0', display: 'flex', alignItems: 'center' }}>
          <Pagination
            page={state.page + 1}
            style={{ display: 'block' }}
            count={Math.ceil(matches.length / state.rowsPerPage)}
            onChange={handleChangePage}
          />
        </Grid>
        {/* */}
        <Grid item md={2} sm={3} xs={6}>
          <Tooltip title="Export results">
            <Button 
              color="primary" 
              variant="text"
              startIcon={<GetApp />} 
              onClick={() => setState(prevState => ({...prevState, open: true}))} 
              style={{ 
                width: '100%',
                height: '100%',
                }}>
              Export
            </Button>
          </Tooltip>
        </Grid>
        <Grid item md={2} sm={3} xs={6} style={{ padding: '.5rem', display: 'flex', alignItems: 'center' }}>
          <Select
            style={{width: '100%'}}
            value={state.rowsPerPage}
            onChange={handleChangeRowsPerPage}>
            <MenuItem value={10}>10 rows per page</MenuItem>
            <MenuItem value={25}>25 rows per page</MenuItem>
            <MenuItem value={50}>50 rows per page</MenuItem>
            <MenuItem value={100}>100 rows per page</MenuItem>
          </Select>
        </Grid>
      </Grid>
      <TableContainer className="tableContainer">
        <Table stickyHeader size="small">
          <colgroup>
            {schema.map((_, schIdx) => (
              <col key={schIdx} style={{ width: `${100 * 1 / schema.length}%` }} />
            ))}
          </colgroup>
          <TableHead>
            {(matches.length > 0)
              ? <TableRow>
                {schema.map((name, idxHead) => (
                  <TableCell className={`cm-m${idxHead} tableCell`} key={idxHead}>
                    {name}
                  </TableCell>
                ))}
              </TableRow>
              :
              <TableRow>
                <TableCell className="tableCell">
                  No matches
                </TableCell>
              </TableRow>
            }
          </TableHead>
          <TableBody>
            {(state.rowsPerPage > 0
              ? matches.slice(
                state.page * state.rowsPerPage,
                state.page * state.rowsPerPage + state.rowsPerPage)
              : matches).map((row, idxRow) => (
                <TableRow key={idxRow} hover style={{ cursor: 'pointer' }} onClick={() => handleMarkText(row)}>
                  {row.map((col, idxCol) => {
                    let match = textEditor.getRange(textEditor.posFromIndex(col[0]), textEditor.posFromIndex(col[1]));
                    return (
                      <TableCell key={idxCol} style={{ padding: 0 }}>
                        <div style={{ padding: '6px 24px 6px 16px' }}>
                          {(match.length > 36)
                            ? match.slice(0, 36).replaceAll(' ', '␣') + '...'
                            : match.replaceAll(' ', '␣')}
                        </div>
                      </TableCell>)
                  }
                  )}
                </TableRow>
              ))}
          </TableBody>
        </Table>
      </TableContainer >
    </>
  )
}

export default ResultsTable;
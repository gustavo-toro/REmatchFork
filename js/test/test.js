const REmatch = require('../lib')
const fs = require('fs');
const { strict } = require('assert');
let expect    = require("chai").expect;

try {
    
    // // Ejemplo find
    // console.time('Tiempo find');
    // const text = 'Lorem ipsum dolor sit amet consectetur adipiscing elit euismod condimentum, conubia a mollis pulvinar nascetur taciti elementum praesent'
    // let rgx1 = REmatch.compile('.*!word{dolor}.*');
    // const result = rgx1.find(text).span('word');
    // console.log(result);
    // console.timeEnd('Tiempo find');

    // // Ejemplo findIter
    // console.time('Tiempo finditer')
    // let rgx2 = REmatch.compile('.*!x{ly}.*');
    // const text1 = "He was carefully disguised but captured quickly by police.";
    // console.log(rgx2.findIter(text1).next().value.span('x'));
    // console.log(rgx2.findIter(text1).next());
    // console.log(rgx2.findIter(text1).next());
    // console.timeEnd('Tiempo finditer')

    // Ejemplo findall
    // console.time('Tiempo findall')
    // const text2 = "He was carefully disguised but captured quickly by police.";
    // let rgx3 = REmatch.compile('.*!adverb{ [a-zA-Z]+ly}.*');
    // let list = rgx3.findall(text2);
    // for (let index = 0; index < list.length; index++) {
    //   const element = list[index].group('adverb');
    //   console.log(element)
    // }
    // console.timeEnd('Tiempo findall')

    // // Error nros
    // const text3 = "sempiternal"
    // let rgx8 = REmatch.compile('.*!word{[a-z]+}.*');
    // let list1 = rgx8.find(text3);
    // console.log(list1.group('word'))
    

    // Error caracteres extraños
    // const correo = 'correo@gmail.com';
    // let match2 = REmatch.find('.*!username{[a-z]+}@!domain{[^@]+}\.[a-z]+.*', correo);
    // console.log(match2.group('username'))

    
    // Error OOM
    // const doc = fs.readFileSync('../../../../RKBExplorer/sparql.log.combo.1', "latin1");
    // let match1 = REmatch.findall('.*sparql!x{[^\n]*OPTIONAL[^\n]*\n}.*', doc);
    // console.log(match1.group('x'));

    // const doc1 = fs.readFileSync('../../../../RKBExplorer/sparql.log.combo.1', "latin1");
    // let match11 = REmatch.find('.*OPTIONAL.*', doc1);
    // console.log(match11.group('x'));
  



    function limpiar(spanners_file) {
      // console.log(spanners_file)
      let r = spanners_file.trim();
      
      r = r.replace(/\t/g, '');
      r = r.replace(/\r/g, '');
      r = r.replace(/\n/g, '');
      
      r = r.replace(/ /g, '');
      
      r = r.replace(/x=\|/gi, '');
      r = r.replace(/y=\|/gi, '');
      r = r.replace(/z=\|/gi, '');
      r = r.replace(/w=\|/gi, '');
      r = r.slice(0, -1)
      
      r = r.split('>');
      // console.log(r)
      resultado = []
      r.forEach(span => {
        // console.log(span)
        span = span.split(',');
        // console.log(span)
        span = Array.from(span, x => parseInt(x))
        // console.log(r)
        if (isNaN(span[0])) {
          span = null
          
        }
        resultado.push(span);
      })
      // console.log(resultado)
      resultado.sort(function(lista1, lista2) {return lista1[0]-lista2[0]});
      return resultado
    }
    // const s = "x = |0,1>    x = |0,2>    x = |0,3>     x = |0,4>	    x = |0,5>	"
    // console.log(limpiar(s));

    
    function getDirectories(path) {
      return fs.readdirSync(path).filter(function (file) {
        return fs.statSync(path+'/'+file).isDirectory();
      });
    }

    tests_folders = getDirectories('../../REmatchEngine/tests/test_input_regex_file')
    tests_folders.forEach((folder) => {
     
      
        describe('Testing all methods ' + folder, function() {
        
            
            let doc = fs.readFileSync('../../REmatchEngine/tests/test_input_regex_file/' + folder + '/document.txt', "latin1");
            let rgx = fs.readFileSync('../../REmatchEngine/tests/test_input_regex_file/' + folder + '/regex.txt', "latin1");
            let spanners = fs.readFileSync('../../REmatchEngine/tests/test_input_regex_file/' + folder + '/spanners.txt', "latin1");
            spanners = limpiar(spanners);
            
            it('should test find method for document ' + folder, function() {
            let rgx1 = REmatch.compile(rgx);
            let result = rgx1.find(doc)

            if (result != null) {
              result = result.span('x');
            
              expect(result).to.eql(spanners[0])
            }
            else {
              expect(result).to.eql(spanners[0])
            }
            
          })
      
        
        
            it('should test findIter method for document ' + folder, function() {
              
              let rgx1 = REmatch.compile(rgx);
              let r_finditer = []
              
              for (let result of rgx1.findIter(doc)) {
                result = result.span('x')
                r_finditer.push(result)
                r_finditer.sort(function(lista1, lista2) {return lista1[0]-lista2[0]});
              }


              // spanners.forEach(spann => {
              //   let result = rgx1.findIter(doc)
              //   // console.log(spann, result.next())
              //   result = result.next().value
              //   if (result!= undefined) {
                  
              //     // console.log(result)
              //     result = result.span('x')
              //     r_finditer.push(result)
              //     r_finditer.sort(function(lista1, lista2) {return lista1[0]-lista2[0]});
              //   }
              //   else {
              //     r_finditer.push(null)
              //   }
                
              // })
              
              
              for(let i = 0; i < r_finditer.length; i++){

                expect(r_finditer[i]).to.eql(spanners[i])
              }
              
              
              
            })

            it('should test findAll method for document ' + folder, function() {
              
              let rgx1 = REmatch.compile(rgx);

              let list = rgx1.findall(doc);
              list.sort(function(macth1, match2) {return macth1.span('x')[0]-match2.span('x')[0]});
              
              for(let i = 0; i < list.length; i++){
                // console.log(list[i].span('x'))
                if (list != null) {
                  expect(list[i].span('x')).to.eql(spanners[i])
                }
                else {
                  expect(list[i]).to.eql(spanners[i])
                }
              } 
          })
        });
      });


} catch (error) {
    console.log('Error:', error)
};
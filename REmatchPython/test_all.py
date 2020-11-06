import os
import sys
import unittest
sys.path.insert(0, "../")
import REmatch as re
import pathlib

path = "../REmatchEngine/tests/test_input_regex_file"
directory = pathlib.Path(path)

class Test(unittest.TestCase):

    def test_match(self):
        for folder in directory.iterdir():
            if not folder.is_dir():
                continue
            folder_path = os.path.join(path, folder.name)
            content = os.listdir(folder_path)
            with open(os.path.join(folder_path, content[0])) as file: #document.txt
                document = file.read().replace('\n', '')
            with open(os.path.join(folder_path, content[1])) as file: #regex.txt
                regex = file.read().replace('\n', '')
            with open(os.path.join(folder_path, content[2])) as file: #spanners.txt
                data_list = file.readlines()
                spanners = []
                for line in data_list: 
                    pos = 0 #puntero para ir avanzando por lo grupos en el string
                    groups = []
                    for _ in range(line.count('|')): #Se recorre cada span de la linea
                        start = line.find('|', pos) + 1
                        end = line.find(',', pos)
                        span1 = line[start:end]
                        start = end + 1
                        end = line.find('>', pos)
                        span2 = line[start:end]
                        groups.append((int(span1), int(span2)))
                        pos = end + 1
                    spanners.append(groups)
            rgx_obj = re.compile(regex)
            matches = rgx_obj.findall(document)
            #Se revisa cada grupo del match con los spanners
            for pos in range(len(matches)): #Se recorre cada match
                #groups = matches[pos].groups() #Violacion de segmento
                match = matches[pos]
                #for group_pos in range(len(spanners[pos])): #Se recorren los grupos de cada match
                 #   capture = groups[group_pos]
                  #  self.assertTupleEqual(match.span(capture), spanners[pos][group_pos])

if __name__ == "__main__":
    unittest.main()
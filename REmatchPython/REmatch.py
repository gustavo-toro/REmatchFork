import sys
sys.path.insert(0, "../REmatchEngine/build/SWIG/bin/SWIG")
import rematch

class Match:

    def __init__(self, match_object, string):
        self.match_object = match_object
        self.variables = match_object.variables()
        self.string = string
        # self.__span = span
        # self.__start = start
        # self.__end = end

    def start(self, capture):
        if str(capture).isnumeric():
            capture = self.variables[capture - 1]
        return self.match_object.span(capture)[0]

    def end(self, capture):
        if str(capture).isnumeric():
            capture = self.variables[capture - 1]
        return self.match_object.span(capture)[1]

    def span(self, capture):
        if str(capture).isnumeric():
            capture = self.variables[capture - 1]
        return self.match_object.span(capture)

    def group(self, capture):
        if str(capture).isnumeric():
            capture = self.variables[capture - 1]
        span = self.match_object.span(capture)
        return self.string[span[0]:span[1]]

    def groups(self):
        matches = []
        for var in self.variables:
            span = self.match_object.span(var)
            matches.append(self.string[span[0]:span[1]])
        return tuple(matches)
    
    def groupdict(self):
        matches = dict()
        for var in self.variables:
            span = self.match_object.span(var)
            matches[var]= self.string[span[0]:span[1]]
        return matches

class Regex:

    def __init__(self, pattern, **flags): # Flags del estilo: save_anchors=True, early_output=True
        self.pattern = pattern
        self.rgx_opts = self.set_flags(flags) #Probar si se pasan todas las flags o es necesario poner **
        self.RegEx = rematch.RegEx(pattern, self.rgx_opts)

    def set_flags(self, flags):
        rgx_opts = rematch.RegExOptions()
        for key, value in flags.items():
            if key == "save_anchors":
                rgx_opts.set_save_anchors(value)
            elif key == "multi_line":
                rgx_opts.set_multi_line(value)
            elif key == "line_by_line":
                rgx_opts.set_line_by_line(value)
            elif key == "dot_nl":
                rgx_opts.set_dot_nl(value)
            elif key == "early_output":
                rgx_opts.set_early_output(value)
        return rgx_opts

    def find(self, string):
        evaluator = self.RegEx.findIter(string)
        match = evaluator.next()
        return Match(match, string)

    def findall(self, string): # Retornar objetos match 
        matches = list()
        while True:
            match = self.RegEx.findIter(string)
            if not match:
                break
            else:
                matches.append(Match(match, string))
        return matches

    def finditer(self, string):
        
        regexIter = self.RegEx.findIter(string)
        while True:
            match = regexIter.next()
            if not match:
                break
            else:
                yield Match(match, string)
        '''
        while True:
            match = self.RegEx.findIter(string)
            if not match:
                break
            else:
                yield Match(match, string)
        '''
    def search(self, string):
        return self.find(string)

    def match(self, string):
        if self.pattern[:2] == ".*":
            pattern = self.pattern[2:]
        else:
            pattern = self.pattern
        print(pattern)
        regEx = rematch.RegEx(pattern, self.rgx_opts)
        return Match(regEx.findIter(string), string)

    def fullmatch(self, string):
        if self.pattern[:2] == ".*" and self.pattern[-2:] == ".*":
            pattern = self.pattern[2:-2]
        else:
            pattern = self.pattern
        regEx = rematch.RegEx(pattern, self.rgx_opts)
        return Match(regEx.findIter(string), string)

def compile(pattern, **flags):
    return Regex(pattern, **flags)
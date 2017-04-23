# -*- coding:utf-8 -*-

import __main__ as mn
import configparser as cp

def __loadConf():
    conf = cp.SafeConfigParser()
    conf.read(mn.basepath + "\\main.ini")
    return conf

def getVarsNames( _vars, symboltable ) :
    """
    This is wrapper of getVarName() for a list references.
    """
    return [ getVarName( var, symboltable ) for var in _vars ]

def __getVarName( var, symboltable, error=None ) :
    """
    Return a var's name as a string.\nThis funciton require a symboltable(returned value of globals() or locals()) in the name space where you search the var's name.\nIf you set error='exception', this raise a ValueError when the searching failed.
    """
    for k,v in symboltable.iteritems() :
        if id(v) == id(var) :
            return k
    else :
        if error == "exception" :
            raise ValueError("Undefined function is mixed in subspace?")
        else:
            return error

def getTableKey(table, value):
    for i in table.keys():
        if table[i] == value:
            return i
    else:
        raise ValueError("Cannot be found the value;" + str(value))

def getConfigContents(**table):
    cf = __loadConf()
    ret = {}
    for i in table.keys():
        ret[i] = {}
        for v in table[i]:
           ret[i][v] = cf.get(i, v)
    return ret

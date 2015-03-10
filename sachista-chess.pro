TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS = movegenerator movegenerator-perft movegenerator-test

movegenerator-perft.depends = movegenerator
movegenerator-test.depends = movegenerator



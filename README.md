# ConfigFileParser
This archive is about Using Flex &amp; Bison to Parse Config Files. The contens is shown below:<br>
* [Description File Design](#description-file-design)
  * [Key-Values](#key-values)
  * [Inheritance Mechanism](#inheritance-mechanism)
  * [Induction Mechanism](#induction-mechanism)
  * [Comments](#comments)
* [Syntax Design](#syntax-design)
* [Usage](#usage)
* [Postscript](#postscript)

## Description File Design
### Key-Values
> Format of the config file is similar to JSON, which is composed of pairs of key-values. The config file is also composed of some tuples, which contain some pairs of key-values. e.g.

```
section {
 key1 = "string";
 key2 = 12.34;
}
```

> Therefore,

```
section.key1=”string”
section.key2=12.34
```
### Inheritance Mechanism
> Besides the features above, the config file also supports inheritance mechanism. The symbol of inheritance is shown by ":", e.g.<br>

```
derived_section : section {
  key1 = "override string";
  key3 = 10;
}
```
> Therefore,

```
derived_section.key1=”override string”
derived_section.key2=12.34
derived_section.key3=10
```
> The types of the config file include int, float, string.<br>

### Induction Mechanism
> The config file also introduces induction mechanism, which is expressed by "include", e.g.<br>
> The contents of a.config:

```
section_a {
 key1 = "string";
 key2 = 12.34;
}
```
> The contents of b.config:

```
#include "a.config"
section_b {
 key1 = "str1";
 key2 = 12.34;
x{
 key1=2;
 key2=8;
}
y : section_b.x{
 key1=20;
 key3=33;
}
}
z:section_a{
key1=”str”;
key2=25;
}
```
### Comments
> The config file also supports comments, formularized by /*comments*/ or //, e.g.<br>

```
//comment
section {
 key1 = /* comment*/ "string";
 key2 = 12.34;
}
```
## Syntax Design
> To parse the config file, flex & bison is of much efficiency. Before using the mature tools, we should define the grammar, which is in the form of Backus–Naur Form. The config file's  Backus–Naur form is shown below:<br>

```
tuples::= tuple tuples | ε
tuples::= ID LB entries RB | ID COLON LB entries RB
entries::= kv entries | tuple entries | ε
kv::= ID EQ value END
value::= FLOAT | INT | ctring | NULLV
cstring::= STRING cstring

INT→ [0-9]+
FLOAT→ [+-]?[0-9]+(\.[0-9]*)?
STRING→ \"(\\.|[^\\"])*\"
ID→ [a-z_][a-z0-9_\.]*
LB→ {
RB→ }
COLON→ :
EQ→ =
END→ ;
NULLV→ NULL
```

## Usage

> To Compile the source code, you need to install git & make. You can use the following command line to complie them:

```
$ git clone https://github.com/lijiansong/ConfigFileParser
$ cd ConfigFileParser
$ make
```
> After the above cmds, you would get an executable file, named *config_parser*, and a static library suffixed by *.a*, named *lib_cfg_parser.a*. You can execute it like this( before use it you need to write a config file that is formulized by the grammar defined above ):

```
$ ./config_parser test.config
```
> You can also call the static library *lib_cfg_parser.a* in your own program.

## Postscript
> To be continued...

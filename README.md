# ConfigFileParser
==================================
Using Flex &amp; Bison to Parse Config Files 

> Format of the config file is similar to JSON, which is composed of pairs of key-values. The config file is also composed of some tuples, which contain some pairs of key-values. e.g.

```
section {
 key1 = "string";
 key2 = 12.34;
}
```
Therefore,
```
section.key1=”string”
section.key2=12.34
```
Besides the features above, the config file also supports inheritance mechanism. The symbol of inheritance is shown by ":", e.g.<br>
```
derived_section : section {
  key1 = "override string";
  key3 = 10;
}
```
Therefore,
```
derived_section.key1=”override string”
derived_section.key2=12.34
derived_section.key3=10
```

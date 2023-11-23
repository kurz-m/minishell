# Minishell

## Description

Minishell is a simple, lightweight Unix shell implemented in pure _C_. This project aims to create a minimalistic shell environment, providing basic shell functionalities for interaction with the UNIX system. It is an educational project to understand how shells work behind the scenes.


## Features

- Parser with abstract syntax tree (*AST*)
- Recursive command execution
- Built-in commands: cd, echo, env, exit, expoort, unset, pwd
- Command history
- Here-docs

## Getting Started

### Dependencies

The program needs readline to be installed either via `brew` on Mac or with the package manager of your choice on your Linux distribution.

### Installing

```bash
git clone https://github.com/kurz-m/minishell.git
cd minishell && make
```

Make automatically checks if the submodules are initialized and if not, it will be done for you.

## Authors

[Fabi](https://github.com/leonfabi)

[Markus](https://github.com/kurz-m)

### Licence

The project is licensed under the GPL - see the [License](LICENCE) file for more details.
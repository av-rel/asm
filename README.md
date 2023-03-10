# Zorasm

# Description
## Zorasm is a assembly like language written for on top of [ZoraVM](https://github.com/av-rel/zoravm). This is rather incomplete but functional with instructions. It is a stack based and low level language.


# Features
- [x] Assembly
- [x] Cross-platform
- [x] Interpreter

# Cons
* Assembly is rather incomplete
* Needs single label defined but cannot jump between other

# How it works?
## It runs on top of Zora Virtual Machine.

# Examples 
[Hello, world](./examples/hw.zsm)
```zorasm
; This will print `Hello, world`

#main
	!push "Hello, world\n"			 ; push to the stack
	!print							 ; Print the top of the mem stack
	!halt 0							 ; exit with status code 0
```

[Exponent](./examples/math.zsm)
```zorasm
#main
    !push 2
    !push 32
    !pow
    !print
    !halt 0

```

## Build from source
```console
gcc main.c -O3 -o zsm
# or
tcc main.c -O3 -o zsm

./zsm run ./examples/hw.zsm
```


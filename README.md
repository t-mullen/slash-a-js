# slash-a-js

Javascript/WASM bindings for the [Slash/A interpreter](https://github.com/arturadib/slash-a).

## Usage
```javascript
// manually create some source code
const source = 'input/0/save/input/add/output/.' // adds x+y

// convert it into bytecode
const bytecode = SlashA.source2ByteCode(source)

// setup the input buffer
const input = new SlashA.VectorDouble()
input.push_back(2)
input.push_back(3)

// set limits on tape size (data and label)
const DATA_SIZE = 10
const LABEL_SIZE = 10

// provide random seed (can be set to some constant for deterministic runs)
const RAND_SEED = Math.floor(Math.random() * 2147483647)

// set limits on runtime and loop depth
const MAX_RUNTIME = 10
const MAX_LOOP_DEPTH = 10

// run the bytecode
const output = SlashA.runByteCode(bytecode, input, DATA_SIZE, LABEL_SIZE, RAND_SEET, MAX_RUNTIME, MAX_LOOP_DEPTH)

// check that the code did not fail (due to runtime or max loop depth being exceeded)
if (SlashA.checkFailed()) {
    throw new Error('Code failed!')
}

// examine output
console.log((new Array(output.size())).map(_, i) => output.get(i)) // [5]

// cleanup
bytecode.delete()
input.delete()
output.delete()
```

Bytecode can also be created directly, without any source code.

```javascript
const bytecode = new SlashA.ByteCode()
bytecode.push_back(1)
```

## Installation
```html
<script>
    var SlashA = {
      onRuntimeInitialized: function () { 
          // ready to use
          const bytecode = new SlashA.ByteCode()
      }
    }
<script>
<script src="build/slash-a.js">
```

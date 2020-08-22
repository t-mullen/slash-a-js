# slash-a-js

Javascript bindings for the Slash/A interpreter.

## Usage
```javascript
const source = "input/0/save/#"
const bytecode = SlashA.source2ByteCode(source)
const inputBuffer = Buffer.alloc(100)
const outputBuffer = Buffer.alloc(100)
const memcore = new SlashA.Memcore(dataTapeLength, labelTapeLength, inputBuffer, outputBuffer)
SlashA.runByteCode(bytecode, memcore, inputBuffer, randomSeed, maxTime, maxLoopDepth)
```

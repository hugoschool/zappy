# Command Buffer

The command circular buffer is essentially made of 2 parts:

- Command holder
- Circular buffer

## Notions

- Head: reading pointer
- Tail: writing pointer

## Command holder

The command holder can hold a maximum of 10 commands at a time.

If the command holder has currently 10 commands, and a client sends another command, this command will be ignored due to spam reasons (see subject).

The command holder is essentially a queue, pushing will cause the current tail to be moved and popping will cause the head to be moved.

## Circular buffer

All command buffers are circular.

The maximum size of a buffer is set by the macro `BUFFER_SIZE`.

A command is considered "complete" and can be popped once it contains the ending sequence (`\n` in our case).

If the buffer exceeds `BUFFER_SIZE`, the buffer wraps around and goes back to 0, essentially overwriting the previous content.

Examples are available on the [circular buffer wikipedia page](https://en.wikipedia.org/wiki/Circular_buffer):

![Circular Buffer](https://upload.wikimedia.org/wikipedia/commons/f/fd/Circular_Buffer_Animation.gif)

---

The command circular buffer can be used as a static library available in `server/src/buffer`.

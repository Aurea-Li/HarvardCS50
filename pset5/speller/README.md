# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

A lung disease caused by inhaling very fine ash and sand dust.

## According to its man page, what does `getrusage` do?

It returns resource usage measures for the calling process, children of the calling process, or the calling thread.

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

Save memory on the computer since passing pointers prevents the computer from creating duplicate variables.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

The words are read one character at a time using 'fgetc' until the end of the file. At each iteration, it is checking if the character
is from the alphabet or is an apostrophe. If it is, it will add it to an array called 'word' which is ultimately what is used for spell check.
If a character is encountered which is not from the alphabet or apostrophe, it will iterate until the end of the word without bothering to save it down
or spell check it, and then start fresh, repeating the cycle for the next word in the file.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

By reading characters at a time we can check the words validity while reading it in. If we used 'fscanf' instead, we would have to read in the word, and THEN create another
loop to check that the word is valid, which is less efficient.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

Because we have no intention of modifying the parameter within the function, so it is safer to declare it as constant
so that the computer can issue an error/warning if we accidentally try to modify it.

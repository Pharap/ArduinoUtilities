# Design & Intent

## Introduction

The purpose of this document is to discuss the design decisions and intent behind various aspects of this library.

## Progmem Facilities

### ProgmemPointer & ProgmemReference

The interesting thing about these classes (from a design perspective) is that they are both wrappers for raw pointers, but each serves a distinct purpose.
This mirrors how ordinary C++ references may in some cases be implemented (by the compiler) as raw pointers.


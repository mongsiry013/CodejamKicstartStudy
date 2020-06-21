#!/usr/bin/env node
'use strict';

const { createInterface } = require('readline');
const rl = createInterface({
  input: process.stdin,
  crlfDelay: Infinity
});

const buf = [];
const prom = [];
let maxBuf = 0;
let maxProm = 0;
rl.on('line', (line) => {
  if (prom.length > 0) {
    maxProm = Math.max(maxProm, prom.length);
    const [resolve, reject] = prom.shift();
    resolve(line);
  } else {
    rl.pause();
    buf.push(line);
    maxBuf = Math.max(maxBuf, buf.length);
  }
});

rl.on('close', () => {
  // console.error({maxProm, maxBuf});
});

async function getLine() {
  return new Promise((resolve, reject) => {
    if (buf.length > 0) {
      const line = buf.shift();
      resolve(line);
    } else {
      prom.push([resolve, reject]);
      rl.resume();
    }
  });
}

function noNines(x) {
  let rem = 0n;
  let to = x - (x % 10n);
  for (let i = to; i <= x; i++) {
    if (i % 9n !== 0n) {
      rem++;
    }
  }
  to /= 10n;
  let i = 0n, mid = 0n;
  while (to > 0n) {
    mid += (to % 10n) * (9n ** i);
    i++;
    to = to / 10n;
  }
  mid *= 8n; 
  return mid + rem;
}

/**
 * 
 * @param {Number} f
 * @param {Number} l
 * @returns {Number}
 */
function solve(f, l) {
  return noNines(l) - noNines(f) + 1n;
}

async function main() {
  const t = Number(await getLine());
  for (let i = 0; i < t; i++) {
    const [f, l] = (await getLine()).split(' ').map(BigInt);
    const res = solve(f, l);
    console.log(`Case #${i+1}:`, res.toString());
  }
}

if (require.main === module) {
  main();
}
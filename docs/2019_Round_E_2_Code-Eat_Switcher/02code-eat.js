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

/**
 * 
 * @param {Number []} slots
 * @param {Number []} days 
 * @returns {String}
 */
function solve(slots, days) {
  const s = slots.length;  
  const d = days.length;  
  slots.sort((a, b) => b[0] * a[1] - a[0] * b[1]);

  const codeSum = [0];
  const eatSum = [];
  eatSum[s] = 0;
  for (let i = 1; i <= s; i++) {
    codeSum[i] = codeSum[i-1] + slots[i-1][0];
    eatSum[s-i] = eatSum[s-i+1] + slots[i-1][1];
  }
  // console.error({slots, codeSum, eatSum});

  const res = [];

  for(let i = 0; i < d; i++) {
    const [a, b] = days[i];

    // binary search for a in codeSum
    let lo = 0, hi = s;
    while (lo <= hi) {
      const mid = Math.floor((lo + hi) / 2);
      if (codeSum[mid] < a) {
        lo = mid + 1;
      } else if (codeSum[mid] > a) {
        hi = mid - 1;
      } else { // codeSum[mid] === a
        hi = mid;
        lo = mid + 1;
        break;
      }
    }
    // console.error({hi, lo, cs: codeSum[hi], es: eatSum[hi], a, b});
    if (hi < s) {
      const cRemain = a - codeSum[hi];
      const eBlock = eatSum[hi+1];
      const [cc, ee] = slots[hi];
      const cr = cRemain / cc;
      const eRemain = ee * (1 - cr);
      // console.error({cRemain, eBlock, cr, eRemain});
      if (eBlock + eRemain >= b) {
        res.push('Y');
      } else {
        res.push('N');
      }
    } else {
      if (codeSum[hi] >= a && b === 0) {
        res.push('Y');
      } else {
        res.push('N');
      }
    }
  }

  return res.join('');
}

async function main() {
  const t = Number(await getLine());
  for (let i = 0; i < t; i++) {
    const [d, s] = (await getLine()).split(' ').map(Number);
    const slots = [], days = [];
    for (let j = 0; j < s; j++) {
      const [cc, ee] = (await getLine()).split(' ').map(Number);
      slots.push([cc,ee]);
    }
    for (let j = 0; j < d; j++) {
      const [aa, bb] = (await getLine()).split(' ').map(Number);
      days.push([aa, bb]);
    }
    const res = solve(slots, days);
    console.log(`Case #${i+1}:`, res);
  }
}

if (require.main === module) {
  main();
}

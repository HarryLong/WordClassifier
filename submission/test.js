const CHARS="abcdefghijklmnopqrstuvwxyz'",VOWELS_REGEX=new RegExp("[aeiou]","gi"),MIN_WORD_LENGTH=2,MAX_WORD_LENGTH=14,MIN_VOWEL_RATIO=.1,MAX_VOWEL_RATIO=.85,DATA_MAPPING=["S|2","S|3","S|4","E|2","E|3","E|4","G|2","G|3","G|4","O|0"],DATA_SEPARATOR=124,DATA_FAULT_TOLERANCE=0;let MAP=[];const initMap=t=>{MAP=DATA_MAPPING.map((()=>[])),setMap(t)},setMap=t=>{let e=0,A=0;t.forEach(((n,i)=>{if(n==DATA_SEPARATOR)A++,e=0;else{let s=DATA_MAPPING[A].split("|"),o=parseInt(s[1]);if(o){if(e%o==0){for(let _="",f=0;o>f;f++)_+=CHARS[t[i+f]];MAP[A].push(_)}}else MAP[A].push(t[i]);e++}}))},testByData=t=>{let e=0;return DATA_MAPPING.forEach(((A,n)=>{A=A.split("|");let i=A[0],s=parseInt(A[1]);if("S"==i){let o=t.substr(0,s);-1!=MAP[n].indexOf(o)&&e++}else if("E"==i){let o=t.substr(-s);-1!=MAP[n].indexOf(o)&&e++}else if("G"==i)for(let _=0;_<t.length-(s-1);_++){let o=t.substr(_,s);-1!=MAP[n].indexOf(o)&&e++}else if("O"==i){for(let f={},_=0;_<t.length;_++)f[t[_]]=f[t[_]]?f[t[_]]+1:1;for(let E in f)f.hasOwnProperty(E)&&f[E]/t.length*255>MAP[n][CHARS.indexOf(E)]&&e++}})),DATA_FAULT_TOLERANCE>=e},testByLength=t=>{return t.length<=MAX_WORD_LENGTH&&t.length>=MIN_WORD_LENGTH},testByVowelRatio=t=>{let e=t.match(VOWELS_REGEX);e=e?e.length:0;let A=e/t.length;return A>=MIN_VOWEL_RATIO&&MAX_VOWEL_RATIO>=A},testWord=t=>t&&testByLength(t)&&testByVowelRatio(t)&&testByData(t);module.exports={init:initMap,test:testWord};
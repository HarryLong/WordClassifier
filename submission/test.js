!function(n,t){const e="abcdefghijklmnopqrstuvwxyz'",i=new RegExp("[aeiou]","gi"),f=[170,153,204,170,170,153,153,127,153,102,170,153,153,153,170,153,102,153,170,153,170,127,153,102,127,153,95],o=2,r=14,u=.1,s=.85,c=["S|2","S|3","E|2","E|3","G|2","G|3","G|4"],l=124,h=0;let g=[];const a=n=>{g=c.map((()=>[])),p(n)},p=n=>{let t=0,i=0;n.forEach(((f,o)=>{if(f==l)i++,t=0;else{let r=c[i].split("|"),u=parseInt(r[1]);if(t%u==0){var s="";for(let h=0;u>h;h++)s+=e[n[o+h]];g[i].push(s)}t++}}))},x=n=>{let t=0;return c.forEach(((e,i)=>{if(!(t>h)){e=e.split("|");let f=e[0],o=parseInt(e[1]);if("S"==f){let r=n.substr(0,o);-1!=g[i].indexOf(r)&&t++}else if("E"==f){let r=n.substr(-o);-1!=g[i].indexOf(r)&&t++}else if("G"==f)for(let u=0;u<n.length-(o-1);u++){let r=n.substr(u,o);-1!=g[i].indexOf(r)&&t++}}})),h>=t},d=n=>{return n.length<=r&&n.length>=o},E=n=>{let t=n.match(i),e=t?t.length/n.length:0;return e>=u&&s>=e},b=n=>{const t={};for(let i=0;i<n.length;i++)t[n[i]]=t[n[i]]?t[n[i]]+1:1;return!Object.keys(t).filter((i=>{let o=Math.floor(t[i]/n.length*255),r=f[e.indexOf(i)];return o>r})).length},O=n=>n&&d(n)&&E(n)&&b(n)&&x(n);module.exports={init:a,test:O},t[""]=n}({},function(){return this}());
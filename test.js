// ==UserScript==
// @name         在洛谷显示 CF 题目的 Accepted(2)
// @namespace    http://tampermonkey.net/
// @version      2024.9.23.1
// @description  CF Accepted
// @author       AbsMatt
// @match        https://www.luogu.com.cn/paste/3urx8brh
// @grant        GM_xmlhttpRequest
// @license      MIT
// @downloadURL https://update.greasyfork.org/scripts/495935/%E5%9C%A8%E6%B4%9B%E8%B0%B7%E6%98%BE%E7%A4%BACF%20difficulty.user.js
// @updateURL https://update.greasyfork.org/scripts/495935/%E5%9C%A8%E6%B4%9B%E8%B0%B7%E6%98%BE%E7%A4%BACF%20difficulty.meta.js
// ==/UserScript==
(async function() {
    localStorage.clear();
    for(let i=2;i<500;i++){
        let name=document.querySelector("#app > div.main-container > main > div.full-container > div > div:nth-child(1) > div.marked > p:nth-child("+i.toString()+")");
        if(!name)break;
        console.log(name.textContent+" finish");
        localStorage.setItem(name.textContent+"wisdom",1);
    }
})();
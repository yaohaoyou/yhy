// ==UserScript==
// @name         在新洛谷自动跳转
// @namespace    http://tampermonkey.net/
// @version      2024.2.26
// @description  luogu.com 自动跳转
// @author       AbsMatt
// @match        https://www.luogu.com/*
// @grant        none
// @license      MIT
// ==/UserScript==

(function() {
    'use strict';
    document.querySelector("#go").click();
})();
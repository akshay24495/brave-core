!function(e){var n={};function t(r){if(n[r])return n[r].exports;var i=n[r]={i:r,l:!1,exports:{}};return e[r].call(i.exports,i,i.exports,t),i.l=!0,i.exports}t.m=e,t.c=n,t.d=function(e,n,r){t.o(e,n)||Object.defineProperty(e,n,{configurable:!1,enumerable:!0,get:r})},t.n=function(e){var n=e&&e.__esModule?function(){return e.default}:function(){return e};return t.d(n,"a",n),n},t.o=function(e,n){return Object.prototype.hasOwnProperty.call(e,n)},t.p="",t(t.s=5)}([,,,,,function(e,n,t){t(6),t(7),t(8),t(9),t(10),e.exports=t(11)},function(e,n,t){"use strict";window.__firefox__||Object.defineProperty(window,"__firefox__",{enumerable:!1,configurable:!1,writable:!1,value:{userScripts:{},includeOnce:function(e,n){return!!__firefox__.userScripts[e]||(__firefox__.userScripts[e]=!0,"function"==typeof n&&n(),!1)}}})},function(e,n,t){"use strict";window.__firefox__.includeOnce("ContextMenu",function(){window.addEventListener("touchstart",function(e){var n=e.target,t=n.closest("a"),r=n.closest("img");if(t||r){var i={};t&&(i.link=t.href),r&&(i.image=r.src,i.title=r.title),(i.link||i.image)&&webkit.messageHandlers.contextMenuMessageHandler.postMessage(i)}},!0)})},function(e,n,t){"use strict";Object.defineProperty(window.__firefox__,"download",{enumerable:!1,configurable:!1,writable:!1,value:function(e,n){if(n===SECURITY_TOKEN){var t=document.createElement("a");t.href=e,t.dispatchEvent(new MouseEvent("click"))}}})},function(e,n,t){"use strict";window.__firefox__.includeOnce("FocusHelper",function(){var e=function(e){var n=e.type,t=e.target.nodeName;("INPUT"===t||"TEXTAREA"===t||e.target.isContentEditable)&&(function(e){if("INPUT"!==e.nodeName)return!1;var n=e.type.toUpperCase();return"BUTTON"==n||"SUBMIT"==n||"FILE"==n}(e.target)||webkit.messageHandlers.focusHelper.postMessage({eventType:n,elementType:t}))},n={capture:!0,passive:!0},t=window.document.body;["focus","blur"].forEach(function(r){t.addEventListener(r,e,n)})})},function(e,n,t){"use strict";var r=function(){return function(e,n){if(Array.isArray(e))return e;if(Symbol.iterator in Object(e))return function(e,n){var t=[],r=!0,i=!1,o=void 0;try{for(var s,a=e[Symbol.iterator]();!(r=(s=a.next()).done)&&(t.push(s.value),!n||t.length!==n);r=!0);}catch(e){i=!0,o=e}finally{try{!r&&a.return&&a.return()}finally{if(i)throw o}}return t}(e,n);throw new TypeError("Invalid attempt to destructure non-iterable instance")}}();window.__firefox__.includeOnce("LoginsHelper",function(){var e=!1;function n(n){e&&alert(n)}var t={_getRandomId:function(){return Math.round(Math.random()*(Number.MAX_VALUE-Number.MIN_VALUE)+Number.MIN_VALUE).toString()},_messages:["RemoteLogins:loginsFound"],_requests:{},_takeRequest:function(e){var n=e,t=this._requests[n.requestId];return this._requests[n.requestId]=void 0,t},_sendRequest:function(e,n){var t=this._getRandomId();n.requestId=t,webkit.messageHandlers.loginsManagerMessageHandler.postMessage(n);var r=this;return new Promise(function(n,i){e.promise={resolve:n,reject:i},r._requests[t]=e})},receiveMessage:function(e){var n=this._takeRequest(e);switch(e.name){case"RemoteLogins:loginsFound":n.promise.resolve({form:n.form,loginsFound:e.logins});break;case"RemoteLogins:loginsAutoCompleted":n.promise.resolve(e.logins)}},_asyncFindLogins:function(e,n){var t=this._getFormFields(e,!1);if(!t[0]||!t[1])return Promise.reject("No logins found");t[0].addEventListener("blur",o);var r=i._getPasswordOrigin(),s=i._getActionOrigin(e);if(null==s)return Promise.reject("Action origin is null");var a={form:e},u={type:"request",formOrigin:r,actionOrigin:s};return this._sendRequest(a,u)},loginsFound:function(e,n){this._fillForm(e,!0,!1,!1,!1,n)},onUsernameInput:function(e){var t=e.target;if(t.ownerDocument instanceof HTMLDocument&&this._isUsernameFieldType(t)){var i=t.form;if(i&&t.value){n("onUsernameInput from",e.type);var o=this._getFormFields(i,!1),s=r(o,3),a=s[0],u=s[1];s[2];if(a==t&&u){var l=this;this._asyncFindLogins(i,{showMasterPassword:!1}).then(function(e){l._fillForm(e.form,!0,!0,!0,!0,e.loginsFound)}).then(null,n)}}}},_getPasswordFields:function(e,t){for(var r=[],i=0;i<e.elements.length;i++){var o=e.elements[i];o instanceof HTMLInputElement&&"password"==o.type&&(t&&!o.value||(r[r.length]={index:i,element:o}))}return 0==r.length?(n("(form ignored -- no password fields.)"),null):r.length>3?(n("(form ignored -- too many password fields. [ got ",r.length),null):r},_isUsernameFieldType:function(e){if(!(e instanceof HTMLInputElement))return!1;var n=e.hasAttribute("type")?e.getAttribute("type").toLowerCase():e.type;return"text"==n||"email"==n||"url"==n||"tel"==n||"number"==n},_getFormFields:function(e,t){var r,i,o=null,s=this._getPasswordFields(e,t);if(!s)return[null,null,null];for(var a=s[0].index-1;a>=0;a--){var u=e.elements[a];if(this._isUsernameFieldType(u)){o=u;break}}if(o||n("(form -- no username field found)"),!t||1==s.length)return[o,s[0].element,null];var l=s[0].element.value,f=s[1].element.value,d=s[2]?s[2].element.value:null;if(3==s.length)if(l==f&&f==d)i=s[0].element,r=null;else if(l==f)i=s[0].element,r=s[2].element;else if(f==d)r=s[0].element,i=s[2].element;else{if(l!=d)return n("(form ignored -- all 3 pw fields differ)"),[null,null,null];i=s[0].element,r=s[1].element}else l==f?(i=s[0].element,r=null):(r=s[0].element,i=s[1].element);return[o,i,r]},_isAutocompleteDisabled:function(e){return!(!e||!e.hasAttribute("autocomplete")||"off"!=e.getAttribute("autocomplete").toLowerCase())},_onFormSubmit:function(e){var t=e.ownerDocument,r=t.defaultView;var o=i._getPasswordOrigin(t.documentURI);if(o){var s=i._getActionOrigin(e),a=this._getFormFields(e,!0),u=a[0],l=a[1],f=a[2];if(null!=l){this._isAutocompleteDisabled(e)||this._isAutocompleteDisabled(u)||this._isAutocompleteDisabled(l)||this._isAutocompleteDisabled(f),0;var d=u?{name:u.name,value:u.value}:null,c={name:l.name,value:l.value};f&&(f.name,f.value),r.opener&&r.opener.top;webkit.messageHandlers.loginsManagerMessageHandler.postMessage({type:"submit",hostname:o,username:d.value,usernameField:d.name,password:c.value,passwordField:c.name,formSubmitURL:s})}}else n("(form submission ignored -- invalid hostname)")},_fillForm:function(e,t,r,i,o,s){var a=this._getFormFields(e,!1),u=a[0],f=a[1];if(null==f)return[!1,s];if(f.disabled||f.readOnly)return n("not filling form, password field disabled or read-only"),[!1,s];var d=Number.MAX_VALUE,c=Number.MAX_VALUE;u&&u.maxLength>=0&&(d=u.maxLength),f.maxLength>=0&&(c=f.maxLength);var m=(s=function(e,n){var t,r,i;if(null==e)throw new TypeError("Array is null or not defined");var o=Object(e),s=o.length>>>0;if("function"!=typeof n)throw new TypeError(n+" is not a function");arguments.length>1&&(t=e);r=new Array(s),i=0;for(;i<s;){var a,u;i in o&&(a=o[i],u=n.call(t,a,i,o),r[i]=u),i++}return r}(s,function(e){return{hostname:e.hostname,formSubmitURL:e.formSubmitURL,httpReal:e.httpRealm,username:e.username,password:e.password,usernameField:e.usernameField,passwordField:e.passwordField}})).filter(function(e){var t=e.username.length<=d&&e.password.length<=c;return t||n("Ignored",e.username),t},this);if(0==m.length)return[!1,s];if(f.value&&!i)return"existingPassword",[!1,s];var g=!1;!r&&(this._isAutocompleteDisabled(e)||this._isAutocompleteDisabled(u)||this._isAutocompleteDisabled(f))&&(g=!0,n("form not filled, has autocomplete=off"));var v=null;if(u&&(u.value||u.disabled||u.readOnly)){var p=u.value.toLowerCase();if((w=m.filter(function(e){return e.username.toLowerCase()==p})).length){for(var _=0;_<w.length;_++){var h=w[_];h.username==u.value&&(v=h)}v||(v=w[0])}else"existingUsername",n("Password not filled. None of the stored logins match the username already present.")}else if(1==m.length)v=m[0];else{var w;v=(w=u?m.filter(function(e){return e.username}):m.filter(function(e){return!e.username}))[0]}var b=!1;if(v&&t&&!g){if(u){var y=u.disabled||u.readOnly,F=v.username!=u.value,L=o&&F&&u.value.toLowerCase()==v.username.toLowerCase();y||L||!F||(u.value=v.username,l(u,"keydown",40),l(u,"keyup",40))}f.value!=v.password&&(f.value=v.password,l(f,"keydown",40),l(f,"keyup",40)),b=!0}else v&&!t?("noAutofillForms",n("autofillForms=false but form can be filled; notified observers")):v&&g&&("autocompleteOff",n("autocomplete=off but form can be filled; notified observers"));return[b,s]}},i={_getPasswordOrigin:function(e,n){return e},_getActionOrigin:function(e){var n=e.action;return""==n&&(n=e.baseURI),this._getPasswordOrigin(n,!0)}};function o(e){t.onUsernameInput(e)}var s=document.body;function a(e){for(var n=0;n<e.length;n++){var t=e[n];"FORM"===t.nodeName?u(t):t.hasChildNodes()&&a(t.childNodes)}return!1}function u(e){try{t._asyncFindLogins(e,{}).then(function(e){t.loginsFound(e.form,e.loginsFound)}).then(null,n)}catch(e){n(e)}}function l(e,n,t){var r=document.createEvent("KeyboardEvent");r.initKeyboardEvent(n,!0,!0,window,0,0,0,0,0,t),e.dispatchEvent(r)}new MutationObserver(function(e){for(var n=0;n<e.length;++n)a(e[n].addedNodes)}).observe(s,{attributes:!1,childList:!0,characterData:!1,subtree:!0}),window.addEventListener("load",function(e){for(var n=0;n<document.forms.length;n++)u(document.forms[n])}),window.addEventListener("submit",function(e){try{t._onFormSubmit(e.target)}catch(e){n(e)}}),Object.defineProperty(window.__firefox__,"logins",{enumerable:!1,configurable:!1,writable:!1,value:Object.freeze(new function(){this.inject=function(e){try{t.receiveMessage(e)}catch(e){}}})})})},function(e,n,t){"use strict";window.__firefox__.includeOnce("PrintHandler",function(){window.print=function(){webkit.messageHandlers.printHandler.postMessage({})}})}]);

const themataCodeEditors = [];
const loadedDynamicAssets = [];
let selfSyntaxHighlightBlocks = [];
const __syntaxHiglightLanguagesRainbow = [
    "c", "coffeescript", "csharp", "css", "d", "generic",
    "go", "haskell", "html", "java", "javascript", "lua",
    "php", "python", "r", "ruby", "scheme", "shell", "smalltalk"
]
const __syntaxHiglightLanguagesSyntaxhighlighterjs = [
    "AS3", "AppleScript", "Bash", "CSharp", "ColdFusion",
    "Cpp", "Css", "Delphi", "Diff", "Erlang", "Groovy", "JScript",
    "Java", "JavaFX", "Perl", "Php", "Plain", "PowerShell", 
    "Python", "Ruby", "Sass", "Scala", "Sql", "Vb", "Xml"
]
const themataSiteVariables = {
    "__themata_base_url__": "",
    "__themata_page_url__": "",
    "__themata_project__": "",
    "__themata_project_github_location__": "",
    "__themata_current_page_path__": "",
    "__themata_current_page_location__": "",
    "__themata_current_page_title__": "",
};
let __themata_github_feedback_type = "page";
const themataCurrentPageLink = window.location.href;

try {
    definedThen(typeof themataSyntaxHighlighter !== "undefined", () => {
        Array.from(gets("highlight")).forEach((item, index) => {
            let language = item.parentNode.className.split(" ").reduce((acc, cn) => {
                if (cn.startsWith("highlight-")) return cn.split("highlight-")[1];
                return acc;
            }, "");
            if (language.includes(",")) {
                selfSyntaxHighlightBlocks.push({
                    element: item,
                    options: language.split(",")
                });
                return;
            }
            if (language === "text") language = "plaintext";
            resolveCodeBlockSyntaxHighlighter([item, 
                `editor-${index}`], 
                language, 
                themataSyntaxHighlighter, 
                themataSyntaxHighlighterTheme, 
                themataCodeBlockIsEditable,
                themataSyntaxHighlighterIframeEmbed);
        });
    });
    if (selfSyntaxHighlightBlocks.length > 0) {
        resolveSyntaxHighlightBlocks();
    }
    definedThen(typeof __themataJsLoadedCallbacks !== "undefined", () => __themataJsLoadedCallbacks.forEach(cb => cb()));
} catch (ex) {
    console.error(ex);
}

window.onload = function() {
    resolveSiteVariables();
    setSiteElementEvents();
    definedThen(typeof __themataOnloadCallbacks !== "undefined", () => __themataOnloadCallbacks.forEach(cb => cb()));
    let highlighted = themataFindGetParameter("highlight");
    if (highlighted && highlighted != "") {
        highlighted = highlighted.replace(/\W+/g, '-').toLowerCase();
        let highlightedSection = document.getElementById(highlighted);
        if (highlightedSection) {
            //console.log(highlighted, highlightedSection);
            highlightedSection.scrollIntoView();
        }
    };
};

function setSiteElementEvents() {
    let pageFeedbackButton = get("__themata__feedback_this_page");
    let productFeedbackButton = get("__themata__feedback_this_product");

    if (!pageFeedbackButton) return;
    pageFeedbackButton.onclick = (e) => renderFeedbackBox("project");
    productFeedbackButton.onclick = (e) => renderFeedbackBox("page");

}

function renderFeedbackBox(type) {
    __themata_github_feedback_type = type;
    document.getElementById("__themata__feedback_buttons_panel").style.display = "none";
    document.getElementById("__themata__feedback_input_panel").style.display = "flex";
    document.getElementById("__themata__feedback_textarea").focus();
}

function themataSubmitGithubFeedback() {
    let text = document.getElementById("__themata__feedback_textarea").value;
    if (__themata_github_feedback_type == "project") {
        if (!(!themataGithubFeedbackProjectTemplate || themataGithubFeedbackProjectTemplate == "")) { // lol
            text = expandAllThemataVaraibles(`${text}
            
            ${themataGithubFeedbackProjectTemplate}`);
        } else {
            text = `${text}
            
---
### Feedback Details

⚠ *Do not edit this section.

* Project Source: [${themataCurrentProject}](${themataCurrentProjectGithubLocation})
* Project: **${themataCurrentProject}**
* Bringer: [themata](https://github.com/Thecarisma/themata)`;
        }
    } else {
        if (!(!themataGithubFeedbackPageTemplate || themataGithubFeedbackPageTemplate == "")) { // lol
            text = expandAllThemataVaraibles(`${text}
            
            ${themataGithubFeedbackPageTemplate}`);
        } else {
            text = `${text}
        
---
### Feedback Details

⚠ *Do not edit this section.

* Page Title: [${themataCurrentPageTitle}](${themataCurrentPageLink})
* Page Source: [${themataCurrentPagePath}](${themataCurrentPageLocation})
* Project: **${themataCurrentProject}**
* Bringer: [themata](https://github.com/Thecarisma/themata)`;
        }
    }
    openInNewTab(`${themataCurrentProjectGithubLocation}/issues/new?title=&body=${encodeURIComponent(text)}`);
    document.getElementById("__themata__feedback_input_panel").style.display = "none";
    document.getElementById("__themata__feedback_label").innerText = "Your feedback has been submited";
    document.getElementById("__themata__feedback_textarea").value = "";
}

function resolveSyntaxHighlightBlocks() {
    selfSyntaxHighlightBlocks.forEach((selfSyntaxHighlightBlock, index) => {
        let syntaxHighlighter;
        let syntaxHighlighterTheme;
        let codeBlockEditable = false;
        let syntaxHighlighterIframeEmbed = false;
        let language = selfSyntaxHighlightBlock.options[0];
        for (let oindex = 0; oindex < selfSyntaxHighlightBlock.options.length; oindex++) {
            let value = selfSyntaxHighlightBlock.options[oindex];
            if (value.includes("syntax_highlighter_iframe_embed")) { syntaxHighlighterIframeEmbed = value.split("=")[1] === "True"; continue; }
            if (value.includes("syntax_highlighter_theme")) { syntaxHighlighterTheme = value.split("=")[1]; continue; }
            if (value.includes("code_block_editable")) codeBlockEditable = value.split("=")[1] === "True";
            if (value.includes("syntax_highlighter")) syntaxHighlighter = value.split("=")[1];
        }
        //console.log(selfSyntaxHighlightBlock, language, syntaxHighlighter, codeBlockEditable, syntaxHighlighterTheme);
        resolveCodeBlockSyntaxHighlighter([selfSyntaxHighlightBlock.element, `ceditor-${index}`], 
            language, 
            syntaxHighlighter, 
            syntaxHighlighterTheme, 
            codeBlockEditable,
            syntaxHighlighterIframeEmbed);
    });
    selfSyntaxHighlightBlocks = [];
}

function resolveCodeBlockSyntaxHighlighter(elandid, language, sh, sht, cbe, embed) {
    if (embed) {
        __themata__internal__resolveCodeBlockSyntaxHighlighterEmbeded(elandid, language, sh, sht, cbe);
    } else {
        __themata__internal__resolveCodeBlockSyntaxHighlighterNonEmbeded(elandid, language, sh, sht, cbe);
    }    
}

function __themata__internal__resolveCodeBlockSyntaxHighlighterEmbeded(elandid, language, sh, sht, cbe) {
    let element;
    let id;
    if (Array.isArray(elandid)) {
        element = elandid[0];
        id = elandid[1];
    } else {
        element = get(elandid);
        id = elandid;
    }
    let sourceCode = escapeHtml(element.innerText)+"\n\n";
    id = `${id}-iframe`;
    element.innerHTML = `<iframe id="${id}" style="display:block; width: 100%; border: none; border-radius: 6px;"></iframe>`;
    let sourceCodeIframe = get(id);
    let sourceCodeIframeDoc = sourceCodeIframe.contentDocument || sourceCodeIframe.contentWindow.document;
    sourceCodeIframeDoc.body.style = "margin: 0px; overflow: hidden; padding: 0px;";
    appendStyle(sourceCodeIframeDoc.head, `* {
            font-family: "Segoe UI","Helvetica Neue","Helvetica",Arial,sans-serif;
            color: #727273;
        }
        code {
            border: none;
            line-height: 1.7;
            overflow-y: hidden;
            height: 100%;
            padding: 2px 10px 4px 0px;
            white-space: pre-wrap;
            word-break: break-word;
        }
        pre {
            padding: 0px;
            margin: 0px;
            overflow: hidden;
            height: 100%;
        }`);
        
    // todo, option to use loader
    if (sh === "highlightjs" 
            || sh === "prism" 
            || sh === "rainbow"
            || sh === "microlight"
            || sh === "google_prettify") {

        sourceCodeIframeDoc.body.innerHTML = `<pre class="prettyprint"><code id="${id}-code-block" class="language-${language} microlight" data-language="${language}">${sourceCode}</code></pre>`;
        themateResizeIframeToFitCode(sourceCodeIframe, `${id}-code-block`);

        if (sh === "highlightjs") {
            let styleLink = (sht.startsWith("http") ? sht : `https://cdnjs.cloudflare.com/ajax/libs/highlight.js/11.5.1/styles/${sht}.min.css`);
            loadStylesheet(sourceCodeIframeDoc.head, styleLink, null);
            loadScript(sourceCodeIframeDoc.head, `https://cdnjs.cloudflare.com/ajax/libs/highlight.js/11.5.1/highlight.min.js`, () => {
                appendScript(sourceCodeIframeDoc.head, `hljs.highlightAll();`);
            });

        } else if (sh === "rainbow") {
            let scriptUrls = __syntaxHiglightLanguagesRainbow.map((lang) => `https://cdnjs.cloudflare.com/ajax/libs/rainbow/1.2.0/js/language/${lang}.min.js`);
            loadMultipleScripts(sourceCodeIframeDoc.head, [`https://cdnjs.cloudflare.com/ajax/libs/rainbow/1.2.0/js/rainbow.min.js`, ...scriptUrls], () => {
                if (!sht || sht === "") sht = "github";
                let styleLink = (sht.startsWith("http") ? sht : `https://cdnjs.cloudflare.com/ajax/libs/rainbow/1.2.0/themes/${sht}.min.css`);
                loadStylesheet(sourceCodeIframeDoc.head, styleLink, () => {
                    appendStyle(sourceCodeIframeDoc.head, `pre { padding: 16px; }`);
                    appendScript(sourceCodeIframeDoc.head, `Rainbow.color();`);
                });
            });

        } else if (sh === "prism") {
            let styleLink = `https://cdnjs.cloudflare.com/ajax/libs/prism/1.27.0/themes/prism-${sht}.min.css`;
            if (!sht || sht === "" || sht === "default") styleLink = "https://cdnjs.cloudflare.com/ajax/libs/prism/1.27.0/themes/prism.min.css";
            loadStylesheet(sourceCodeIframeDoc.head, (sht.startsWith("http") ? sht : styleLink), () => {
                loadScript(sourceCodeIframeDoc.head, `${themataStaticAssetsDir}prism.js`);
            });

        } else if (sh === "google_prettify") {
            let skin = (!sht || sht === "" || sht === "default") ? "" : `skin=${sht}`;
            loadScript(sourceCodeIframeDoc.head, `https://cdn.rawgit.com/google/code-prettify/master/loader/run_prettify.js?${skin}`, () => {
                appendStyle(sourceCodeIframeDoc.head, "pre.prettyprint { padding: 16px !important; }");
            });

        } else if (sh === "microlight") {
            loadScript(sourceCodeIframeDoc.head, `${themataStaticAssetsDir}microlight.js`, () => {
                appendStyle(sourceCodeIframeDoc.head, `pre { padding: 16px; }`);
                appendScript(sourceCodeIframeDoc.head, `microlight.reset();`);
            });

        }
        
    } else if (sh === "syntaxhighlighterjs") { // damn this highlighter
        sourceCodeIframeDoc.body.innerHTML = `<pre class="brush: ${language}">${sourceCode}</pre>`;
        let scriptUrls = __syntaxHiglightLanguagesSyntaxhighlighterjs.map((lang) => `https://cdnjs.cloudflare.com/ajax/libs/SyntaxHighlighter/3.0.83/scripts/shBrush${lang}.min.js`);
        loadMultipleScripts(sourceCodeIframeDoc.head, [`https://cdnjs.cloudflare.com/ajax/libs/SyntaxHighlighter/3.0.83/scripts/shCore.min.js`, ...scriptUrls], () => {
            if (!sht || sht === "") sht = "Default";
            loadStylesheet(sourceCodeIframeDoc.head, `https://cdnjs.cloudflare.com/ajax/libs/SyntaxHighlighter/3.0.83/styles/shCore.min.css`, () => {
                let styleLink = (sht.startsWith("http") ? sht : `https://cdnjs.cloudflare.com/ajax/libs/SyntaxHighlighter/3.0.83/styles/shCore${sht}.min.css`);
                loadStylesheet(sourceCodeIframeDoc.head, styleLink, () => {
                    appendStyle(sourceCodeIframeDoc.head, ".syntaxhighlighter table td.code .container { padding: 16px !important; }");
                    appendScript(sourceCodeIframeDoc.head, `SyntaxHighlighter.all();`);
                });
            });
        });

    } else if (sh === "ace" || sh === "syntaxy") {

        sourceCodeIframeDoc.body.innerHTML = `<div id="${id}-code-block" class="ace-editor" data-type="markup">${sourceCode}</div>`;
        themateResizeIframeToFitCode(sourceCodeIframe, `${id}-code-block`, ((sourceCode.split("\n").length+1) * 20));

        if (sh === "ace") {
            loadScript(sourceCodeIframeDoc.head, `https://cdnjs.cloudflare.com/ajax/libs/ace/1.4.14/ace.js`, () => {
                appendStyle(sourceCodeIframeDoc.head, ".ace-editor { font-size: inherit; }");
                appendScript(sourceCodeIframeDoc.head, `
                    let editor = ace.edit("${id}-code-block");
                    editor.setTheme("ace/theme/${sht}");
                    editor.session.setMode("ace/mode/${language}");
                    editor.setOptions({
                        maxLines: Infinity,
                        readOnly: ${!cbe}
                    });
                `);
            });

        } else if (sh === "syntaxy") {
            if (!sht || sht === "" || sht === "default") sht = "light";
            let styleLink = (sht.startsWith("http") ? sht : `${themataStaticAssetsDir}syntaxy.${sht}.min.css`);
            loadStylesheet(sourceCodeIframeDoc.head, styleLink, () => {
                loadScript(sourceCodeIframeDoc.head, `${themataStaticAssetsDir}syntaxy.min.js`, () => {
                    appendScript(sourceCodeIframeDoc.head, `new Syntaxy(document.getElementById("${id}-code-block"), {}).render();`);
                });
            });
        }
        //if (editor) themataCodeEditors.push(editor);
    }
}

function __themata__internal__resolveCodeBlockSyntaxHighlighterNonEmbeded(elandid, language, sh, sht, cbe) {
    let element;
    let id;
    if (Array.isArray(elandid)) {
        element = elandid[0];
        id = elandid[1];
    } else {
        element = get(elandid);
        id = elandid;
    }
    if (sh === "highlightjs" 
            || sh === "prism" 
            || sh === "rainbow"
            || sh === "microlight"
            || sh === "google_prettify") {

        if (sh === "highlightjs" && typeof hljs === "undefined" && !loadedDynamicAssets.includes(`https://cdnjs.cloudflare.com/ajax/libs/highlight.js/11.5.1/highlight.min.js`)) {
            loadScript(null, `https://cdnjs.cloudflare.com/ajax/libs/highlight.js/11.5.1/highlight.min.js`, () => {
                let styleLink = (sht.startsWith("http") ? sht : `https://cdnjs.cloudflare.com/ajax/libs/highlight.js/11.5.1/styles/${sht}.min.css`);
                loadStylesheet(null, styleLink, () => {
                    appendStyle(null, "pre { padding: 0px; }");
                    loadedDynamicAssets.push(`https://cdnjs.cloudflare.com/ajax/libs/highlight.js/11.5.1/highlight.min.js`);
                    __themata__internal__resolveCodeBlockSyntaxHighlighterNonEmbeded(elandid, language, sh, sht, cbe);
                });
            });
            return;

        } else if (sh === "rainbow" && typeof Rainbow === "undefined" && !loadedDynamicAssets.includes(`https://cdnjs.cloudflare.com/ajax/libs/rainbow/1.2.0/js/rainbow.min.js`)) {
            let scriptUrls = __syntaxHiglightLanguagesRainbow.map((lang) => `https://cdnjs.cloudflare.com/ajax/libs/rainbow/1.2.0/js/language/${lang}.min.js`);
            loadMultipleScripts(null, [`https://cdnjs.cloudflare.com/ajax/libs/rainbow/1.2.0/js/rainbow.min.js`, ...scriptUrls], () => {
                if (!sht || sht === "") sht = "github";
                let styleLink = (sht.startsWith("http") ? sht : `https://cdnjs.cloudflare.com/ajax/libs/rainbow/1.2.0/themes/${sht}.min.css`);
                loadStylesheet(null, styleLink, () => {
                    loadedDynamicAssets.push(`https://cdnjs.cloudflare.com/ajax/libs/rainbow/1.2.0/js/rainbow.min.js`);
                    __themata__internal__resolveCodeBlockSyntaxHighlighterNonEmbeded(elandid, language, sh, sht, cbe);
                });
            });
            return;

        } else if (sh === "prism" && typeof Rainbow === "undefined" && !loadedDynamicAssets.includes(`${themataStaticAssetsDir}prism.js`)) {
            let styleLink = `https://cdnjs.cloudflare.com/ajax/libs/prism/1.27.0/themes/prism-${sht}.min.css`;
            if (!sht || sht === "" || sht === "default") styleLink = "https://cdnjs.cloudflare.com/ajax/libs/prism/1.27.0/themes/prism.min.css";
            loadStylesheet(null, (sht.startsWith("http") ? sht : styleLink), () => {
                loadScript(null, `${themataStaticAssetsDir}prism.js`, () => {
                    loadedDynamicAssets.push(`${themataStaticAssetsDir}prism.js`);
                    __themata__internal__resolveCodeBlockSyntaxHighlighterNonEmbeded(elandid, language, sh, sht, cbe);
                });
            });
            return;

        } else if (sh === "google_prettify" && !loadedDynamicAssets.includes(`https://cdn.rawgit.com/google/code-prettify/master/loader/run_prettify.js`)) {
            loadScript(null, `https://cdn.rawgit.com/google/code-prettify/master/loader/run_prettify.js?skin=${sht}`, () => {
                appendStyle(null, "pre.prettyprint { padding: 16px !important; }");
                loadedDynamicAssets.push(`https://cdn.rawgit.com/google/code-prettify/master/loader/run_prettify.js`);
                __themata__internal__resolveCodeBlockSyntaxHighlighterNonEmbeded(elandid, language, sh, sht, cbe);
            });
            return;

        } else if (sh === "microlight" && !loadedDynamicAssets.includes(`${themataStaticAssetsDir}microlight.js`)) {
            loadScript(null, `${themataStaticAssetsDir}microlight.js`, () => {
                loadedDynamicAssets.push(`${themataStaticAssetsDir}microlight.js`);
                __themata__internal__resolveCodeBlockSyntaxHighlighterNonEmbeded(elandid, language, sh, sht, cbe);
                microlight.reset();
            });
            return;
            
        }

        element.className = "";
        element.innerHTML = `<pre class="prettyprint"><code class="language-${language} microlight" data-language="${language}">${escapeHtml(element.innerText)}</code></pre>`;
        element.style.display = "block";

        if (sh === "highlightjs") {
            hljs.highlightAll();
        } else if (sh === "rainbow") {
            Rainbow.color();
        } else if (sh === "microlight") {
            microlight.reset();
        }

    } else if (sh === "syntaxhighlighterjs") {
        if (!loadedDynamicAssets.includes(`https://cdnjs.cloudflare.com/ajax/libs/SyntaxHighlighter/3.0.83/scripts/shCore.min.js`)) {
            let scriptUrls = __syntaxHiglightLanguagesSyntaxhighlighterjs.map((lang) => `https://cdnjs.cloudflare.com/ajax/libs/SyntaxHighlighter/3.0.83/scripts/shBrush${lang}.min.js`);
            loadMultipleScripts(null, [`https://cdnjs.cloudflare.com/ajax/libs/SyntaxHighlighter/3.0.83/scripts/shCore.min.js`, ...scriptUrls], () => {
                if (!sht || sht === "") sht = "Default";
                loadStylesheet(null, `https://cdnjs.cloudflare.com/ajax/libs/SyntaxHighlighter/3.0.83/styles/shCore.min.css`, () => {
                    let styleLink = (sht.startsWith("http") ? sht : `https://cdnjs.cloudflare.com/ajax/libs/SyntaxHighlighter/3.0.83/styles/shCore${sht}.min.css`);
                    loadStylesheet(null, styleLink, () => {
                        appendStyle(null, ".syntaxhighlighter table td.code .container { padding: 16px !important; }");
                        loadedDynamicAssets.push(`https://cdnjs.cloudflare.com/ajax/libs/SyntaxHighlighter/3.0.83/scripts/shCore.min.js`);
                        __themata__internal__resolveCodeBlockSyntaxHighlighterNonEmbeded(elandid, language, sh, sht, cbe);
                    });
                });
            });
            return;
        }

        element.className = "";
        element.innerHTML = `<pre class="brush: ${language}">${escapeHtml(element.innerText)}</pre>`;
        element.style.display = "block";
        SyntaxHighlighter.all();

    } else if (sh === "ace" || sh === "syntaxy") {
        if (sh === "ace" && typeof ace === "undefined" && !loadedDynamicAssets.includes(`https://cdnjs.cloudflare.com/ajax/libs/ace/1.4.14/ace.js`)) {
            loadScript(null, `https://cdnjs.cloudflare.com/ajax/libs/ace/1.4.14/ace.js`, () => {
                appendStyle(null, ".ace-editor { font-size: inherit; }");
                loadedDynamicAssets.push(`https://cdnjs.cloudflare.com/ajax/libs/ace/1.4.14/ace.js`);
                __themata__internal__resolveCodeBlockSyntaxHighlighterNonEmbeded(elandid, language, sh, sht, cbe);
            });
            return;

        } if (sh === "syntaxy" && typeof Syntaxy === "undefined") {
            if (!sht || sht === "" || sht === "default") sht = "light";
            if (!loadedDynamicAssets.includes(`${themataStaticAssetsDir}syntaxy.${sht}.min.css`)) {
                let styleLink = (sht.startsWith("http") ? sht : `${themataStaticAssetsDir}syntaxy.${sht}.min.css`);
                loadStylesheet(null, styleLink, () => {
                    loadScript(null, `${themataStaticAssetsDir}syntaxy.min.js`, () => {
                        loadedDynamicAssets.push(`${themataStaticAssetsDir}syntaxy.${sht}.min.css`);
                        __themata__internal__resolveCodeBlockSyntaxHighlighterNonEmbeded(elandid, language, sh, sht, cbe);
                    });
                });                
                return;
            }
        }
        element.id = id;
        element.style.display = "block";
        element.className = "ace-editor";
        element.setAttribute("data-type", "markup");
        element.innerHTML = escapeHtml(element.innerText);
        let editor;
        if (sh === "ace") {
            editor = ace.edit(id);
            editor.setTheme(`ace/theme/${sht}`);
            editor.session.setMode(`ace/mode/${language}`);
            editor.setOptions({
                maxLines: Infinity,
                readOnly: !cbe
            });
            //console.log("ELEMENT", element);
        } else if (sh === "syntaxy") {
            new Syntaxy(get(id), {}).render();
        }
        if (editor) themataCodeEditors.push(editor);
    }
    
}

// resolve for text too
function resolveSiteVariables() {
    themataSiteVariables["__themata_base_url__"] = window.location.origin;
    themataSiteVariables["__themata_page_url__"] = window.location.href;
    themataSiteVariables["__themata_project__"] = themataCurrentProject;
    themataSiteVariables["__themata_project_github_location__"] = themataCurrentProjectGithubLocation;
    themataSiteVariables["__themata_current_page_path__"] = themataCurrentPagePath;
    themataSiteVariables["__themata_current_page_location__"] = themataCurrentPageLocation;
    themataSiteVariables["__themata_current_page_title__"] = themataCurrentPageTitle;
    Object.keys(themataSiteVariables).forEach(themataSiteVariable => {
        let variableValue = themataSiteVariables[themataSiteVariable];
        let innerHTMLBaseElements = [ "strong", "em", "span", "p", "a", "div" ];
        innerHTMLBaseElements.forEach(innerHTMLBaseElement => {
            let nodes = xpathSelector(`//${innerHTMLBaseElement}[contains(., '${themataSiteVariable}')]`);
            nodes.forEach(node => {
                node.innerHTML = node.innerHTML.replace(new RegExp(themataSiteVariable+"E", 'g'), "__THEMATA_PENDING_REVERSE_PLACING__");
                node.innerHTML = node.innerHTML.replace(new RegExp(themataSiteVariable, 'g'), variableValue);
            });
        });
        innerHTMLBaseElements.forEach(innerHTMLBaseElement => {
            let nodes = xpathSelector(`//${innerHTMLBaseElement}[contains(., '__THEMATA_PENDING_REVERSE_PLACING__')]`);
            nodes.forEach(node => node.innerHTML = node.innerHTML.replace(new RegExp("__THEMATA_PENDING_REVERSE_PLACING__", 'g'), themataSiteVariable));
        });
        nodes = xpathSelector(`//a[contains(@href, '${themataSiteVariable}')]`);
        nodes.forEach(node => node.href = node.href.replace(themataSiteVariable, themataSiteVariables[themataSiteVariable]));
    });
}

function getThemataCodeEditors() {
    return themataCodeEditors;
}

function setThemataCodeEditorMode(mode) {
    themataCodeEditors.forEach(themataCodeEditor => themataCodeEditor.setMode(mode));
}

function setThemataCodeEditorTheme(theme) {
    themataCodeEditors.forEach(themataCodeEditor => themataCodeEditor.setTheme(theme));
}

function setThemataCodeEditorOptions(options) {
    themataCodeEditors.forEach(themataCodeEditor => themataCodeEditor.setOptions(options));
}

function expandAllThemataVaraibles(text) {
    Object.keys(themataSiteVariables).forEach(themataSiteVariable => { 
        text = text.replace(new RegExp(themataSiteVariable, 'g'), themataSiteVariables[themataSiteVariable]);
    });
    return text;
}

function openInNewTab(url) {
    window.open(url, '_blank').focus();
}

function definedThen(expr, cb) {
    if (expr) cb();
}

function get(idOrClassName) {
    let element = document.getElementById(idOrClassName);
    if (element) return element;
    return gets(idOrClassName)[0] || element ;
}

function gets(name) {
    let elements = document.getElementsByClassName(name);
    if (!elements.length) elements = document.getElementsByName(name);
    if (!elements.length) elements = document.getElementsByTagName(name);
    //if (!elements.length) elements = document.getElementsByTagNameNS(name);
    return elements;
}

function xpathSelector(selector) {
    let result = [];
    let evaluation = document.evaluate(selector, document, null, XPathResult.ANY_TYPE, null);
    let value = evaluation.iterateNext();
    while (value) {
        result.push(value);
        value = evaluation.iterateNext();
    }
    return result;
}

function qs(query) {
    return document.querySelector(query);
}

function themataForEach(array, fn) {
    if (Array.isArray(array) || array.forEach) array.forEach((entry, index) => fn(entry, index));
    else fn(entry, index);
}

function escapeHtml(unsafe) {
    return unsafe.replaceAll('&', '&amp;')
        .replaceAll('<', '&lt;')
        .replaceAll('>', '&gt;')
        .replaceAll('"', '&quot;')
        .replaceAll("'", '&#039;');
}

function themateResizeIframeToFitCode(iframe, id, height) {
    let iframeDocument = iframe.contentDocument || iframe.contentWindow.document;
    if (height) {
        iframe.style.height = `${height}px`;
        return;
    }
    let embededCodeElement = iframeDocument.getElementById(id);
    iframe.style.height = (embededCodeElement.parentNode.scrollHeight+30) + "px";
}

function loadScript(headd, url, callback) {
    var head = headd || document.head;
    var script = document.createElement('script');
    script.type = 'text/javascript';
    script.src = url;
    script.onreadystatechange = callback;
    script.onload = callback;
    head.appendChild(script);
}

function loadMultipleScripts(headd, urls, callback) {
    let urlCount = 0;
    for (let url of urls) {
        loadScript(headd, url, () => {
            urlCount++;
            if (urlCount === urls.length) callback();
        });
    }
}

function loadStylesheet(headd, url, callback) {
    var head = headd || document.head;
    var script = document.createElement('link');
    script.type = 'text/css';
    script.href = url;
    script.rel = "stylesheet";
    script.onreadystatechange = callback;
    script.onload = callback;
    head.appendChild(script);
}

function appendStyle(headd, css) {
    var head = headd || document.head;
    var style = document.createElement('style');
    style.type = 'text/css';
    if (style.styleSheet){
        style.styleSheet.cssText = css;
    } else {
        style.appendChild(document.createTextNode(css));
    }
    head.appendChild(style);
}

function appendScript(headd, content) {
    var head = headd || document.head;
    var script = document.createElement('script');
    script.innerHTML = content;
    head.appendChild(script);
}

function themataFindGetParameter(parameterName) {
    var result = null,
        tmp = [];
    location.search
        .substr(1)
        .split("&")
        .forEach(function (item) {
          tmp = item.split("=");
          if (tmp[0] === parameterName) result = decodeURIComponent(tmp[1]);
        });
    return result;
}


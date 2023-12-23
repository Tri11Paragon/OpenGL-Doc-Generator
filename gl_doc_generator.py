from bs4 import BeautifulSoup
import requests
import re
import sys

def open_url(url):
    return BeautifulSoup(requests.get(url).content, "html.parser")

def extract(o):
    if o == None:
        return ""
    else:
        return o.get_text()
    
def replace_tag(element, old_tag_str, new_tag_str, **kwargs):
    elements = element.find_all(old_tag_str, **kwargs)
    for tag in elements:
            new_tag = soup.new_tag(new_tag_str)
            new_tag.string = tag.text
            tag.replace_with(new_tag)

def process_paragraphs(p_tags):
    paragraphs = []
    for p in p_tags:
        replace_tag(p, "code", 'b')
        text = p.get_text()
        text = re.sub("\n[\s]+", " ", text)
        text = text.replace("\n", "")
        if text.isspace() or len(text) == 0:
            continue
        paragraphs.append(text.strip())
    return paragraphs

def limit_width(line, padding_str = "", first_str = None, width = 120):
    if (first_str == None):
        first_str = padding_str
    results = []
    line_str = ""
    is_first = True
    needs_new_line = False
    for i, c in enumerate(line):
        if (i % width == width - 1):
            needs_new_line = True
        if (needs_new_line and c == ' '):
            if (is_first):
                results.append(first_str + line_str)
                is_first = False
            else:
                results.append(padding_str + line_str)
            line_str = ""
            needs_new_line = False
        else:
            line_str += c
    if (is_first):
        results.append(first_str + line_str)
    else:
        results.append(padding_str + line_str)
    return results

def process_name(div):
    v = extract(div.find("p")).split('—')
    if len(v) == 1:
        return "@name" + v[0]
    str = "@name " + v[0] + "-"
    for i in range(1, len(v)):
        str += v[i]
    return str

def process_spec(div):
    tables = div.find_all("table", class_="funcprototype-table")
    funcs = []
    for table in tables:
        func = ""
        rows = table.find_all("tr")
        for row in rows:
            datas = row.find_all("td")
            for data in datas:
                text = data.get_text()
                if text is None or text.isspace():
                    continue
                func += text.replace("\n", "").replace("\r", "")
        funcs.append("@code " + func + " @endcode")
    return funcs

def process_params(div):
    if div is None:
        return []
    parent = div.find("div", class_="variablelist").find(class_="variablelist")
    list = parent.find_all(recursive=False)

    params = []
    for p,d in zip(list[::2], list[1::2]):
        param = p.get_text().replace("\n", "")
        d = d.find()
        replace_tag(d, "code", 'b')
        line = ""
        for content in d.contents:
            line += re.sub("\n[\s]+", " ", str(content))

        line_copy = ""
        for i, c in enumerate(line):
            line_copy += c
            if (c == '.' or c == ',' ) and (i + 1 < len(line)):
                if line[i + 1] != ' ':
                    line_copy += ' '
        line = line_copy.strip()

        param_str = "@param " + param + " "
        padding_str = ""
        for i in range(len(param_str)):
            padding_str += ' '
        params.extend(limit_width(line, padding_str, param_str))
    return params

def process_desc(div):
    if div is None:
        return []
    div = div.find_all('p')

    pg = process_paragraphs(div)
    results = []
    for f in pg:
        results.extend(limit_width("\t" + f))
        results[-1] += "<br>"

    return results

def process_notes(div):
    if div is None:
        return []
    div = div.find_all('p')

    pg = process_paragraphs(div)
    results = []
    param = "@note "
    padd = ""
    for i in range(len(param)):
        padd += " "
    for f in pg:
        results.extend(limit_width(f, padd, param))

    return results

def process_errors(div):
    if div is None:
        return []
    div = div.find_all('p')

    pg = process_paragraphs(div)
    results = []
    param = "@errors "
    padd = ""
    for i in range(len(param)):
        padd += " "
    for f in pg:
        results.extend(limit_width(f, padd, param))

    return results

def process_seealso(div):
    if div is None:
        return []
    div = div.find('p').find_all('a')

    alsos = []
    for a in div:
        text = a.get_text()
        alsos.append("@see " + text)

    return alsos

def process_page(url):
    global soup
    soup = open_url(url)
    ref = soup.find("div", class_="refentry")

    if ref is None:
        print("NULL")
        return

    name_div = ref.find("div", class_="refnamediv")
    cspec_div = ref.find("div", class_="refsynopsisdiv").find("div", class_="funcsynopsis")
    parameters_div = ref.find("div", id="parameters")
    description_div = ref.find("div", id="description")
    notes_div = ref.find("div", id="notes")
    associatedgets_div = ref.find("div", id="associatedgets")
    errors_div = ref.find("div", id="errors")
    seealso_div = ref.find("div", id="seealso")

    print("/**")
    print(" * " + process_name(name_div))
    print(" * @usage")
    for f in process_spec(cspec_div):
        print(" * " + f)
    for f in process_params(parameters_div):
        print(" * " + f)
    print(" * @description")
    for f in process_desc(description_div):
        print(" * " + f);
    print(" * ")
    for f in process_notes(notes_div):
        print(" * " + f)
    print(" * ")
    for f in process_errors(errors_div):
        print(" * " + f)
    print(" * ")
    for f in process_seealso(seealso_div):
        print(" * " + f)
    print(" */")

# process_page("https://registry.khronos.org/OpenGL-Refpages/gl4/html/glClearColor.xhtml")
#process_page("https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBlendEquationSeparate.xhtml")
    
if (len (sys.argv) > 1):
    process_page(sys.argv[1])
else:
    print("Please provide the site to load")
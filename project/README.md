# My TOOLBOX

I created a website consisting of some useful pages for my daily life, using HTML, CSS, JAVASCRIPT, BOOTSTRAP, PYTHON, and FLASK.

## General Technical Info
Using Flask, the pages demonstrate the same header and the footer, except for the active status. Each page which is active will shows the navebar corresponding link dark. The brand at the top left corner is the link to the main page (viewing `index.html`). Each link beside the brand on the header will lead the user to a proper page. On the top right corner is a google search box that will open a new window for the searching result.

While the window is narrowing, the navbar collapse into a button on the top right corner with the brand still staying in its place. This button collaping is possible by using bootstrap (but, unlike the bootstrap example in their documentation, the link items align in center). The custom css file and js file are stored separately in *static* folder.

## Landing Page
This is a very simple page, showing a theme picture just beneath the navbar followed by the explanation of the website with `h3` heading.

## ToDo Page
ToDos page can add an item to do for my daily life. This page uses `localStorage` to store *todo* data in the browser. To add a new item, simply click the **New Task** button (triggering `newTask()`). These items will show in the list even after restart the browser. By directly clicking the item, I can remove it from the list (working with a javascript function, `deleteTask()`). If I want to delete all the items, just click the **Remove All** button (achieved by `clearAll()`).

## Converters Page
This page gives me useful information on American measuring units. If I simply put a number in any box in this page, the equivalent of it will appear in real time on the other side of the arrow image. The boxes in each row are connected by a javascript function. I can convert *cm* to *inch*, *cm* to *foot-inch*, *m* to *yard*, *km* to *mile*, and vise vers, for distance, by typing any side of the arrow image. For weight and temperature, my input number can be translated in the same way (*kg* to *pound*, *celsius* to *fahrenheit*, and vice versa).

## etc Page
In etc page, I draw tables for the information I need. The first table is about blood pressure, the second presents the calories of popular foods (**to me**), and the last one introduces the fare of NYC public transportations. And, each table is separated by a `<hr>` tag decorated by teh custom css file.

import tkinter as tk
root = tk.Tk()
root.title("Hello World")
root.geometry("300x200")
s=tk.StringVar()
s.set("Please Click Me!")
l=tk.Label(root, textvariable=s)
l.pack()
isClicked=False
def on_button_click():
    global isClicked
    global s

    if not isClicked:
        s.set("Button Clicked!")
        isClicked=True
    else:
        s.set("Please Click Me!")
        isClicked=False
b=tk.Button(root, text="Click Me", command=on_button_click)
b.pack()
root.mainloop()
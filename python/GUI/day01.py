import tkinter as tk
from tkinter import ttk
root = tk.Tk()
root.resizable(False,False)
ttk.Label(master=root,text="label").grid(column=0, row=0)

root.mainloop()


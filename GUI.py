import tkinter as tk

def toggle_grid(event):
    x, y = canvas.canvasx(event.x), canvas.canvasy(event.y)
    grid_x, grid_y = int(x / cell_size), int(y / cell_size)
    if grid[grid_x][grid_y] == 0:
        canvas.create_rectangle(grid_x * cell_size, grid_y * cell_size,
                                (grid_x + 1) * cell_size, (grid_y + 1) * cell_size, fill='black')
        grid[grid_x][grid_y] = 1

root = tk.Tk()
root.title("Resizable Grid")

canvas = tk.Canvas(root, width=400, height=400, bg="white")
canvas.pack(fill=tk.BOTH, expand=True)

cell_size = 20  # Size of each cell
cols = canvas.winfo_width() // cell_size
rows = canvas.winfo_height() // cell_size
grid = [[0 for _ in range(rows)] for _ in range(cols)]

canvas.bind("<Button-1>", toggle_grid)

def center_origin(event):
    canvas.update_idletasks()
    canvas_x, canvas_y = canvas.winfo_width(), canvas.winfo_height()
    canvas.create_line(canvas_x / 2, 0, canvas_x / 2, canvas_y, fill='red')
    canvas.create_line(0, canvas_y / 2, canvas_x, canvas_y / 2, fill='red')

center_button = tk.Button(root, text="Center Origin", command=center_origin)
center_button.pack()

def add_static_object():
    # Implement your code here to add a static object to block the algorithm
    pass

add_static_object_button = tk.Button(root, text="Add Static Object", command=add_static_object)
add_static_object_button.pack()

root.mainloop()

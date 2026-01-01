import matplotlib.pyplot as plt
import matplotlib.patches as patches


def draw_linked_list(values):
    fig, ax = plt.subplots()

    x = 0
    box_width = 1.5
    box_height = 0.8
    spacing = 0.5

    for i, value in enumerate(values):
        rect = patches.Rectangle(
            (x, 0),
            box_width,
            box_height,
            fill=False
        )
        ax.add_patch(rect)

        ax.text(
            x + box_width / 2,
            box_height / 2,
            str(value),
            ha="center",
            va="center"
        )

        if i < len(values) - 1:
            ax.arrow(
                x + box_width,
                box_height / 2,
                spacing,
                0,
                head_width=0.1,
                head_length=0.15,
                length_includes_head=True
            )

        x += box_width + spacing

    ax.set_aspect("equal")
    ax.axis("off")
    plt.title("Linked List Visualization")
    plt.savefig("linked_list.png")
    plt.close()

if __name__ == "__main__":
    draw_linked_list([10, 20, 30])

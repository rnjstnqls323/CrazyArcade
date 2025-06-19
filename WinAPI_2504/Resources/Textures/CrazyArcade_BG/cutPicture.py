from PIL import Image
import os

def split_image_horizontally(filename, cols):
    # 이미지 열기
    try:
        image = Image.open(filename)
    except FileNotFoundError:
        print("파일을 찾을 수 없습니다.")
        return

    width, height = image.size
    piece_width = width // cols

    basename = os.path.splitext(os.path.basename(filename))[0]
    output_folder = f"{basename}_slices"

    # 출력 폴더 생성
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    for i in range(cols):
        left = i * piece_width
        right = left + piece_width
        box = (left, 0, right, height)

        cropped_image = image.crop(box)
        output_path = os.path.join(output_folder, f"{basename}_{i}.png")
        cropped_image.save(output_path)

    print(f"{cols}개의 이미지로 저장 완료! → '{output_folder}' 폴더에 있음.")

# 실행 예시
if __name__ == "__main__":
    filename = input("PNG 파일 이름을 입력하세요 (예: myimage.png): ")
    cols = int(input("가로로 자를 개수를 입력하세요: "))
    split_image_horizontally(filename, cols)